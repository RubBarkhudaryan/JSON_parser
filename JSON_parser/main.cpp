#include "parser.h"

int main()
{
	std::vector<std::string> result = parseJSON("./data.json");

	printParsedJSON(result);
}