#include "Network.h"
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <vector>
#include "Node.h"
#include "Edge.h"
#include <map>
#include "PowerPlant.h"
#include <filesystem>

#include <fstream>
#include "json.hpp"

Network::~Network()
{
	for (auto &pair : nodes)
	{
		delete pair.second;
	}
	for (auto &edge : edges)
	{
		delete edge;
	}
}

void Network::addNode(Node *node)
{
	if (!node)
	{
		throw std::invalid_argument("Node nem lehet null.");
	}
	const std::string &id = node->getID();
	if (nodes.count(id))
	{
		throw std::invalid_argument("Node ezzel az Id-val mar letezik.");
	}
	nodes[id] = node;
}

void Network::addEdge(const std::string &fromID, const std::string &toID, double length, double voltageLevel,
					  double resistance, double reactance)
{
	Node *from = getNodebyID(fromID);
	Node *to = getNodebyID(toID);
	if (!from || !to)
	{
		throw std::invalid_argument("Minden node-nak leteznie kell a halozatban.");
	}

	edges.emplace_back(new Edge(from, to, length, voltageLevel, resistance, reactance));
}

Node *Network::getNodebyID(const std::string &id) const
{
	auto it = nodes.find(id);
	return (it != nodes.end()) ? it->second : nullptr;
}

const std::vector<Edge *> &Network::getEdges() const
{
	return edges;
}

void Network::printNetworkInfo() const
{
	std::cout << std::endl
			  << "--- Halozat csomopontjai ---" << std::endl;
	for (const auto &pair : nodes)
	{
		std::cout << pair.second->info() << std::endl;
	}
	std::cout << std::endl
			  << "--- Halozat elei---" << std::endl;
	for (const auto &edge : edges)
	{
		std::cout << edge->info() << std::endl;
	}
}

using json = nlohmann::json;
namespace fs = std::filesystem;

void Network::exportToJson(const std::string &filename) const
{
	fs::path pathToFile(filename);
	fs::path dir = pathToFile.parent_path();

	if (!dir.empty() && !fs::exists(dir))
	{
		fs::create_directories(dir);
	}

	json j;
	j["nodes"] = json::array();
	j["edges"] = json::array();

	for (const auto &pair : nodes)
	{
		const std::string &id = pair.first;
		const auto &nodePtr = pair.second;

		std::string type = nodePtr->getType();
		json nodeJson = {{"id", id}, {"type", type}};

		if (type == "PowerPlant")
		{
			const PowerPlant *pp = dynamic_cast<const PowerPlant *>(nodePtr);
			if (pp)
			{
				nodeJson["plantType"] = pp->getPlantType();
			}
		}

		j["nodes"].push_back(nodeJson);
	}

	for (const auto &edge : edges)
	{
		j["edges"].push_back({{"source", edge->getFromID()},
							  {"target", edge->getToID()}});
	}

	std::ofstream file(filename);
	file << j.dump(4);
}