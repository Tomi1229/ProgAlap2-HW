#pragma once
#include "Network.h"
#include <string>

class DataLoader {
public:
    static void loadNetworkFromTextFile(const std::string& filePath, Network& network);
};