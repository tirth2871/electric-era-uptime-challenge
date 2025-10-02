#include "utils.h"
#include <fstream>
#include <stdexcept>

double getSystemUptime() {
    std::ifstream uptimeFile("/proc/uptime");
    if (!uptimeFile.is_open()) {
        throw std::runtime_error("Failed to open /proc/uptime");
    }

    double uptimeSeconds;
    uptimeFile >> uptimeSeconds;
    return uptimeSeconds;
}
