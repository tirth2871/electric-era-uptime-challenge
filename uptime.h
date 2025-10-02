#ifndef UPTIME_H
#define UPTIME_H

#include <vector>
#include <cstdint>
#include <utility>

struct Interval {
    uint64_t start, end;
};

int computeStationUptime(const std::vector<std::pair<Interval, bool>>& chargerReports);

#endif
