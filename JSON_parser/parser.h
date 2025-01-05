#pragma once

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <regex>


std::vector<std::string> parseJSON(const std::string& filePath);

void printParsedJSON(const std::vector<std::string>& parsedJSON);

std::size_t fileLength(const std::string& filePath);