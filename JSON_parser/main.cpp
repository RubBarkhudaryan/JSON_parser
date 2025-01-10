#include "parser.h"

int main()
{
	std::vector<std::string> strResult = JSONToStringArr("./data.json");

	std::map<std::string, std::variant<double, bool, std::nullptr_t, std::string>> result = parseJSON(strResult);

	for (const auto& pair : result)
	{
		std::cout << pair.first << " => ";

		std::visit(
			[](const auto& value) {

				std::cout << value << "\n";
			},
			pair.second
		);
	}
}