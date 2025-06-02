#pragma once
#include <string>
#include <vector>
#include <map>
#include "Node.h"
#include "Edge.h"

class Network
{
private:
	std::map<std::string, Node*> nodes;
	std::vector<Edge*> edges;

public:

	Network() = default;
	~Network();

	void addNode(Node* node);

	void addEdge(const std::string& fromID, const std::string& toID, double lenght, double voltageLevel,
		double resistance = 0.0, double reactance = 0.0);

	Node* getNodebyID (const std::string& id) const;
	const std::vector<Edge*>& getEdges() const;

	void printNetworkInfo() const;

	void exportToJson(const std::string& filename) const;


};

