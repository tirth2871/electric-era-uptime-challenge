#include "uptime.h"
#include <algorithm>
#include <climits>

int computeStationUptime(const std::vector<std::pair<Interval, bool>>& chargerReports) {
    if (chargerReports.empty()) return 0;

    uint64_t minStart = UINT64_MAX, maxEnd = 0;
    for (auto& r : chargerReports) {
        minStart = std::min(minStart, r.first.start);
        maxEnd = std::max(maxEnd, r.first.end);
    }
    uint64_t totalTime = maxEnd - minStart;
    if (totalTime == 0) return 0;

    std::vector<Interval> upIntervals;
    for (auto& r : chargerReports) {
        if (r.second) upIntervals.push_back(r.first);
    }

    if (upIntervals.empty()) return 0;

    std::sort(upIntervals.begin(), upIntervals.end(),
              [](auto& a, auto& b){ return a.start < b.start; });

    uint64_t upTime = 0;
    uint64_t currStart = upIntervals[0].start;
    uint64_t currEnd = upIntervals[0].end;

    for (size_t i = 1; i < upIntervals.size(); i++) {
        if (upIntervals[i].start > currEnd) {
            upTime += (currEnd - currStart);
            currStart = upIntervals[i].start;
            currEnd = upIntervals[i].end;
        } else {
            currEnd = std::max(currEnd, upIntervals[i].end);
        }
    }
    upTime += (currEnd - currStart);

    return (int)((upTime * 100) / totalTime);
}
