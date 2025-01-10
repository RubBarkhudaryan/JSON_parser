#pragma once

#include <iostream>
#include <fstream>

#include <utility>
#include <string>
#include <vector>
#include <map>

#include <variant>
#include <regex>


std::vector<std::string> JSONToStringArr(const std::string& filePath);

void printParsedJSON(const std::vector<std::string>& parsedJSON);

std::size_t fileLength(const std::string& filePath);

std::pair<std::string, std::variant<double, bool, std::nullptr_t, std::string>> convertValue(const std::string& jsonStr);

std::map<std::string, std::variant<double, bool, std::nullptr_t, std::string>> parseJSON(const std::vector<std::string>& jsonStr);
