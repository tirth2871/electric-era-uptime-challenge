#include "parser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <set>

std::map<int, std::vector<std::pair<Interval, bool>>> parseInputFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open input file");
    }

    std::map<int, std::vector<int>> stationToChargers;
    std::map<int, int> chargerToStation;
    std::map<int, std::vector<std::pair<Interval, bool>>> stationReports;

    std::string line;
    bool inStations = false, inReports = false;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (line == "[Stations]") { inStations = true; inReports = false; continue; }
        if (line == "[Charger Availability Reports]") { inStations = false; inReports = true; continue; }

        std::stringstream ss(line);

        if (inStations) {
            int stationId; ss >> stationId;
            int chargerId;
            while (ss >> chargerId) {
                stationToChargers[stationId].push_back(chargerId);
                chargerToStation[chargerId] = stationId;
            }
        }

        if (inReports) {
            int chargerId; uint64_t start, end; std::string upStr;
            ss >> chargerId >> start >> end >> upStr;
            bool up = (upStr == "true");
            int stationId = chargerToStation[chargerId];
            stationReports[stationId].push_back({{start, end}, up});
        }
    }

    return stationReports;
}
