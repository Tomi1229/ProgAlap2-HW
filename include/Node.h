#pragma once

#include <string>

using namespace std;

class Node
{
protected:
	std::string id;

public:
	Node(const std::string &id);
	virtual ~Node() = default;

	virtual std::string getID() const = 0;

	virtual std::string info() const = 0;

	virtual std::string getType() const = 0;
};
