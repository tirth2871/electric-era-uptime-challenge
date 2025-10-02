#ifndef PARSER_H
#define PARSER_H

#include "uptime.h"
#include <map>
#include <vector>
#include <string>

std::map<int, std::vector<std::pair<Interval, bool>>> parseInputFile(const std::string& filepath);

#endif
