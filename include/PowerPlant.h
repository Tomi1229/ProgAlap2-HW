#pragma once
#include "Node.h"
#include <string>

enum class PowerPlantType
{
	THERMO,
	NUCLEAR,
	HYDRO,
	WIND,
	BIOMASS,
	SOLAR,
	OTHER
};

class PowerPlant : public Node
{
private:
	double powerOutput;
	double voltage;
	PowerPlantType type;

public:
	PowerPlant(const std::string &id, double powerOutput, double voltage, PowerPlantType type);

	void setPowerOutput(double powerOutput);
	void setVoltage(double voltage);
	void setType(PowerPlantType type);

	double getPowerOutput() const;
	double getVoltage() const;
	std::string getPlantType() const;

	std::string getType() const override;
	std::string getID() const override;
	std::string info() const override;
};