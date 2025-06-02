/*#include "DataLoader.h"
#include "PowerPlant.h"
#include "TransformerStation.h"
#include "UserEndpoint.h"
#include "sqlite3.h"
#include <stdexcept>
#include <string>
#include "sqlite3.c"

namespace
{
    struct StmtGuard
    {
        sqlite3_stmt *stmt = nullptr;
        StmtGuard(sqlite3_stmt *s) : stmt(s) {}
        ~StmtGuard()
        {
            if (stmt)
                sqlite3_finalize(stmt);
        }
    };

    void throwIf(int rc, sqlite3 *db, const char *msg)
    {
        if (rc != SQLITE_OK && rc != SQLITE_ROW && rc != SQLITE_DONE)
        {
            std::string err = msg;
            if (db)
                err += ": " + std::string(sqlite3_errmsg(db));
            throw std::runtime_error(err);
        }
    }
}

void DataLoader::loadNetworkFromDatabase(const std::string &dbPath, Network &network)
{
    sqlite3 *db = nullptr;
    int rc = sqlite3_open(dbPath.c_str(), &db);
    throwIf(rc, db, "Nem sikerült megnyitni az adatbázist");

    try
    {
        const char *nodeSql =
            "SELECT id, type, attribute1, attribute2, attribute3, attribute4 FROM Nodes;";
        sqlite3_stmt *rawStmt = nullptr;
        rc = sqlite3_prepare_v2(db, nodeSql, -1, &rawStmt, nullptr);
        throwIf(rc, db, "Nem sikerült előkészíteni a Nodes lekérdezést");
        StmtGuard nodeStmt(rawStmt);

        while ((rc = sqlite3_step(rawStmt)) == SQLITE_ROW)
        {
            std::string id = reinterpret_cast<const char *>(sqlite3_column_text(rawStmt, 0));
            std::string type = reinterpret_cast<const char *>(sqlite3_column_text(rawStmt, 1));

            if (type == "PowerPlant")
            {
                double power = sqlite3_column_double(rawStmt, 2);
                double voltage = sqlite3_column_double(rawStmt, 3);
                bool isPeak = sqlite3_column_double(rawStmt, 4) > 0.5;
                std::string plantTypeStr = reinterpret_cast<const char *>(sqlite3_column_text(rawStmt, 5));

                PowerPlantType plantType;

                if (plantTypeStr == "NUCLEAR")
                    plantType = PowerPlantType::NUCLEAR;
                else if (plantTypeStr == "HYDRO")
                    plantType = PowerPlantType::HYDRO;
                else if (plantTypeStr == "GEOTHERMAL")
                    plantType = PowerPlantType::GEOTHERMAL;
                else if (plantTypeStr == "THERMAL")
                    plantType = PowerPlantType::THERMAL;
                else
                    plantType = PowerPlantType::OTHER;

                network.addNode(new PowerPlant(id, power, voltage, plantType));
            }
            else if (type == "TransformerStation")
            {
                double inVolt = sqlite3_column_double(rawStmt, 2);
                double outVolt = sqlite3_column_double(rawStmt, 3);

                network.addNode(new TransformerStation(id, inVolt, outVolt));
            }
            else if (type == "UserEndpoint")
            {
                double q = sqlite3_column_double(rawStmt, 2);
                double cap = sqlite3_column_double(rawStmt, 3);
                double ind = sqlite3_column_double(rawStmt, 4);
                std::string eTypeStr = reinterpret_cast<const char *>(sqlite3_column_text(rawStmt, 5));

                UserEndpoint::EndpointType etype = (eTypeStr == "CITY")
                                                       ? UserEndpoint::EndpointType::CITY
                                                       : UserEndpoint::EndpointType::INDUSTRIAL;

                network.addNode(new UserEndpoint(id, etype, q, cap, ind));
            }
            else
            {
                throw std::runtime_error("Ismeretlen node típus: " + type);
            }
        }
        throwIf(rc, db, "Hiba a Nodes tábla feldolgozása közben");

        const char *edgeSql =
            "SELECT from_id, to_id, length, voltage, resistance, reactance FROM Edges;";
        rawStmt = nullptr;
        rc = sqlite3_prepare_v2(db, edgeSql, -1, &rawStmt, nullptr);
        throwIf(rc, db, "Nem sikerült előkészíteni az Edges lekérdezést");
        StmtGuard edgeStmt(rawStmt);

        while ((rc = sqlite3_step(rawStmt)) == SQLITE_ROW)
        {
            std::string from = reinterpret_cast<const char *>(sqlite3_column_text(rawStmt, 0));
            std::string to = reinterpret_cast<const char *>(sqlite3_column_text(rawStmt, 1));
            double length = sqlite3_column_double(rawStmt, 2);
            double voltage = sqlite3_column_double(rawStmt, 3);
            double res = sqlite3_column_double(rawStmt, 4);
            double reac = sqlite3_column_double(rawStmt, 5);

            network.addEdge(from, to, length, voltage, res, reac);
        }
        throwIf(rc, db, "Hiba az Edges tábla feldolgozása közben");

        sqlite3_close(db);
    }
    catch (...)
    {
        sqlite3_close(db);
        throw;
    }
}

*/
#include "DataLoader.h"
#include "PowerPlant.h"
#include "TransformerStation.h"
#include "UserEndpoint.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void DataLoader::loadNetworkFromTextFile(const std::string& filePath, Network& network) {
    std::ifstream infile(filePath);
    if (!infile.is_open()) {
        throw std::runtime_error("Nem sikerult megnyitni a fajlt: " + filePath);
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "NODE") {
            std::string type, id;
            iss >> type >> id;

            if (type == "PowerPlant") {
                double power, voltage;
                std::string plantTypeStr;
                int isPeakInt;
                iss >> power >> voltage >> plantTypeStr >> isPeakInt;

                PowerPlantType pType = PowerPlantType::OTHER;
                if (plantTypeStr == "NUCLEAR") pType = PowerPlantType::NUCLEAR;
                else if (plantTypeStr == "THERMO") pType = PowerPlantType::THERMO;
                else if (plantTypeStr == "HYDRO") pType = PowerPlantType::HYDRO;
                else if (plantTypeStr == "BIOMASS") pType = PowerPlantType::BIOMASS;
                else if (plantTypeStr == "WIND") pType = PowerPlantType::WIND;
                else if (plantTypeStr == "SOLAR") pType = PowerPlantType::SOLAR;

                network.addNode(new PowerPlant(id, power, voltage, pType));
            }
            else if (type == "TransformerStation") {
                double inV, outV;
                iss >> inV >> outV;
                network.addNode(new TransformerStation(id, inV, outV));
            }
            else if (type == "UserEndpoint") {
                std::string endpointTypeStr;
                double q, cap, ind;
                iss >> endpointTypeStr >> q >> cap >> ind;

                UserEndpoint::EndpointType etype =
                    (endpointTypeStr == "CITY") ? UserEndpoint::EndpointType::CITY
                    : UserEndpoint::EndpointType::INDUSTRIAL;

                network.addNode(new UserEndpoint(id, etype, q, cap, ind));
            }
        }
        else if (keyword == "EDGE") {
            std::string from, to;
            double length, voltage, r, x;
            iss >> from >> to >> length >> voltage >> r >> x;

            network.addEdge(from, to, length, voltage, r, x);
        }
    }
}