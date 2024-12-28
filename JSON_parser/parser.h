#pragma once

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <regex>


std::vector<std::string> parseJSON(std::string filePath);

void printParsedJSON(std::vector<std::string> parsedJSON);

std::size_t fileLength(std::string filePath);
