#pragma once
#include "Node.h"
#include <string>

class Edge
{
private:
	Node *from;
	Node *to;
	double length;
	double voltageLevel;
	double reactance;
	double resistance;

public:
	Edge(Node *from, Node *to, double length, double voltageLevel, double reactance, double resistance);

	Node *getFrom() const;
	Node *getTo() const;
	double getLength() const;
	double getVoltageLevel() const;
	double getReactance() const;
	double getResistance() const;

	std::string info() const;
	std::string getType() const;
	std::string getToID() const;
	std::string getFromID() const;
};