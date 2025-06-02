#pragma once

#include "Node.h"
#include <string>

Node::Node(const std::string &id) : id(id) {}

std::string Node::getID() const
{
	return id;
}