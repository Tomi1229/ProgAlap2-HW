#include <cstdlib> 
#include <iostream>
#include "Network.h"
#include "DataLoader.h"

int main() {
    std::string file;
    std::cout << "Add meg a bemeneti .txt fajl nevet: ";
    std::getline(std::cin, file);

    try {
        Network network;
        DataLoader::loadNetworkFromTextFile(file, network);
        network.printNetworkInfo();

        network.exportToJson("web/network.json");

        std::cout << "\nSikeres betoltes es exportalas: network.json\n";
        std::cout << "A vizualizalo szerver inditasa...\n";

        system("python server.py");
    }
    catch (const std::exception& ex) {
        std::cerr << "Hiba: " << ex.what() << std::endl;
    }

    return 0;
}