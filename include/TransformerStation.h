#pragma once
#include <string>
#include "Node.h"

class TransformerStation : public Node
{
private:
	double inputVoltage;
	double outputVoltage;

public:
	TransformerStation(const std::string &id, double inputVoltage, double outputVoltage);

	double getInputVoltage() const;
	double getOutputVoltage() const;

	std::string info() const override;

	std::string getType() const override
	{
		return "TransformerStation";
	}
};
