#include "state_machine.h"
#include "parser.h"
#include "uptime.h"
#include <iostream>
#include <map>
#include <stdexcept>

void runStateMachine(const char* filepath) {
    State state = State::INIT;

    std::map<int, std::vector<std::pair<Interval, bool>>> stationReports;
    std::map<int, int> results;

    while (state != State::EXIT && state != State::ERROR) {
        switch (state) {
            case State::INIT:
                std::cerr << "[INFO] Initializing..." << std::endl;
                state = State::PARSE;
                break;

            case State::PARSE:
                try {
                    stationReports = parseInputFile(filepath);
                    state = State::CALCULATE;
                } catch (const std::exception& e) {
                    std::cerr << "[ERROR] " << e.what() << std::endl;
                    state = State::ERROR;
                }
                break;

            case State::CALCULATE:
                for (auto& kv : stationReports) {
                    results[kv.first] = computeStationUptime(kv.second);
                }
                state = State::PRINT;
                break;

            case State::PRINT:
                for (auto& kv : results) {
                    std::cout << kv.first << " " << kv.second << "\n";
                }
                state = State::EXIT;
                break;

            case State::ERROR:
                std::cout << "ERROR" << std::endl;
                state = State::EXIT;
                break;

            case State::EXIT:
                break;
        }
    }
}
