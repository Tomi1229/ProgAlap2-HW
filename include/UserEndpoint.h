#pragma once
#include "Node.h"
#include <string>

class UserEndpoint : public Node
{
public:
	enum class EndpointType
	{
		CITY,
		INDUSTRIAL
	};

private:
	EndpointType type;
	double apparentPower;
	double capacitiveLoad;
	double inductiveLoad;

public:
	UserEndpoint(const std::string &id, EndpointType type, double apparentPower, double capacitiveLoad, double inductiveLoad);

	double getApparentPower() const;
	double getCapacitiveLoad() const;
	double getInductiveLoad() const;
	// EndpointType getType() const;
	std::string info() const override;

	std::string getType() const override;
};
