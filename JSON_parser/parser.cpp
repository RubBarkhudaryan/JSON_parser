#include "parser.h"

std::size_t fileLength(std::string filePath)
{
	std::size_t length{};

	std::string line;

	std::ifstream file;

	file.open(filePath);

	if (file)
	{
		while (std::getline(file, line))
			++length;

		file.close();
	}

	return length;
}

std::vector<std::string> parseJSON(std::string filePath)
{
	std::vector<std::string> result;

	std::ifstream file;

	std::regex valid_property("\\s\"(.*)\":(.*)");

	file.open(filePath);

	if (file)
	{
		std::string text = "";
		std::string temp = "";

		std::size_t length = fileLength(filePath);
		std::size_t it = 0;

		result.push_back("{\n");

		while (std::getline(file, text) && it < length) {

			if (text.empty() || it == 0 || it == length-1)
			{
				++it;
				continue;
			}

			if (std::regex_match(text, valid_property) && it < length)
			{
				if (!temp.empty())
					result.push_back(temp);
				temp = "";
			}

			temp += (text + '\n');
			++it;
		}

		result.push_back(temp);

		result.push_back("}\n");

		file.close();
	}

	return result;
}


void printParsedJSON(std::vector<std::string> parsedJSON)
{
	for (int i = 0; i < parsedJSON.size(); ++i)
		std::cout << i + 1 << " " << parsedJSON[i];
}


/*
*
* basic manipulations read and write in data.json

	std::ofstream newFile("./data.json");

	newFile << "{\n\"obj\":\"Hello world\"\n}";

	newFile.close();

	std::ifstream readFile("./data.json");

	std::string myText;

	while (getline(readFile, myText)) {
		std::cout << myText;
	}

*/