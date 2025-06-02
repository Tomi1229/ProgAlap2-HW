#include "Edge.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>


Edge::Edge(Node *from, Node *to, double length, double voltageLevel, double reactance, double resistance)
	: from(from), to(to), length(length), voltageLevel(voltageLevel), reactance(reactance), resistance(resistance)
{
	if (length <= 0.0 || voltageLevel <= 0.0)
	{
		throw std::invalid_argument("Length and voltage level must be positive.");
	}

	if (reactance < 0.0 || resistance < 0.0)
	{
		throw std::invalid_argument("Reactance and resistance must be non-negative.");
	}

	if (from == nullptr || to == nullptr)
	{
		throw std::invalid_argument("From and to nodes must not be null.");
	}
}

Node *Edge::getFrom() const
{
	return from;
}

Node *Edge::getTo() const
{
	return to;
}

double Edge::getLength() const
{
	return length;
}

double Edge::getVoltageLevel() const
{
	return voltageLevel;
}

double Edge::getReactance() const
{
	return reactance;
}

double Edge::getResistance() const
{
	return resistance;
}

std::string Edge::info() const
{
	std::ostringstream oss;
	oss << "Edge from " << from->getID() << " to " << to->getID() << "\n"
		<< "  Length: " << std::fixed << std::setprecision(1) << length << " km\n"
		<< "  Voltage Level: " << voltageLevel << " kV\n"
		<< "  Reactance: " << reactance << " ohm/km\n"
		<< "  Resistance: " << resistance << " ohm/km";
	return oss.str();
}

std::string Edge::getType() const
{
	return "Edge";
}
std::string Edge::getToID() const
{
	return to->getID();
}
std::string Edge::getFromID() const
{
	return from->getID();
}
