#include "PowerPlant.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>



PowerPlant::PowerPlant(const std::string &id, double powerOutput, double voltage, PowerPlantType type) : Node(id), powerOutput(powerOutput), voltage(voltage), type(type)
{
	if (powerOutput <= 0.0 || voltage <= 0.0)
	{
		throw std::invalid_argument("Pozitiv ertekek szuksegesek.");
	}
}





double PowerPlant::getPowerOutput() const
{
	return powerOutput;
}

double PowerPlant::getVoltage() const
{
	return voltage;
}

std::string PowerPlant::getType() const
{
	return "PowerPlant";
}

std::string PowerPlant::getID() const
{
	return id;
}

std::string PowerPlant::getPlantType() const {
	switch (type) {
	case PowerPlantType::THERMO: return "thermo";
	case PowerPlantType::NUCLEAR: return "nuclear";
	case PowerPlantType::HYDRO: return "hydro";
	case PowerPlantType::BIOMASS: return "biomass";
	case PowerPlantType::WIND: return "wind";
	case PowerPlantType::SOLAR: return "solar";
	default: return "unknown";
	}
}

std::string PowerPlant::info() const
{
	std::ostringstream oss;
	oss << std::endl<< "PowerPlant ID: " << id << "\n"
		<< "  Output: " << std::fixed << std::setprecision(2) << powerOutput << " MW\n"
		<< "  Voltage: " << std::fixed << std::setprecision(2) << voltage << " kV";
	return oss.str();
}