#include "UserEndpoint.h"
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>

UserEndpoint::UserEndpoint(const std::string &id, EndpointType type, double apparentPower, double capacitiveLoad, double inductiveLoad) : Node(id), type(type), apparentPower(apparentPower), capacitiveLoad(capacitiveLoad), inductiveLoad(inductiveLoad)
{
	if (apparentPower <= 0.0)
	{
		throw std::invalid_argument("Apparent power must be positive.");
	}
	if (capacitiveLoad < 0.0)
	{
		throw std::invalid_argument("Capacitive load must be non-negative.");
	}
	if (inductiveLoad < 0.0)
	{
		throw std::invalid_argument("Inductive load must be non-negative.");
	}
}

std::string UserEndpoint::getType() const
{
	return (type == EndpointType::CITY) ? "City" : "Industrial";
}

double UserEndpoint::getApparentPower() const
{
	return apparentPower;
}

double UserEndpoint::getCapacitiveLoad() const
{
	return capacitiveLoad;
}

double UserEndpoint::getInductiveLoad() const
{
	return inductiveLoad;
}
std::string UserEndpoint::info() const {
	std::string typeStr = (type == EndpointType::CITY) ? "City" : "Industrial";
	std::ostringstream oss;

	oss << "UserEndpoint\n";
	oss << "  ID:              " << id << '\n';
	oss << "  Type:            " << typeStr << '\n';
	oss << "  Apparent Power:  " << apparentPower << " MVA\n";
	oss << "  Capacitive Load: " << capacitiveLoad << " kvar\n";
	oss << "  Inductive Load:  " << inductiveLoad << " kvar";

	return oss.str();
}
