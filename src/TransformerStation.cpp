#include "TransformerStation.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>

TransformerStation::TransformerStation(const std::string& id, double powerOutput, double voltage)
	: Node(id), inputVoltage(inputVoltage), outputVoltage(outputVoltage) 
{
	
	if (inputVoltage >= 0.0 || outputVoltage >= 0.0) {
		throw std::invalid_argument("Must be positive.");
	}
}

double TransformerStation::getInputVoltage() const {
	return inputVoltage;
}

double TransformerStation::getOutputVoltage() const {
	return outputVoltage;
}

std::string TransformerStation::info() const
{
	std::ostringstream oss;
	oss << std::endl << "TransformerStation ID: " << id << "\n"
		<< "  Input Voltage:  " << std::fixed << std::setprecision(2) << inputVoltage << " kV\n"
		<< "  Output Voltage: " << std::fixed << std::setprecision(2) << outputVoltage << " kV";
	return oss.str();
}


