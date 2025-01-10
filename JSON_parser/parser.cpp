#include "parser.h"

std::size_t fileLength(const std::string& filePath)
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

std::vector<std::string> JSONToStringArr(const std::string& filePath)
{
    std::vector<std::string> result;

    std::ifstream file(filePath);

    std::regex multilevel_prop_check("\\s*\"([a-zA-Z0-9_-]+)\"\\s*[\:]\\s*(([\[])|([\{]))\\s*");

    if (file)
    {
        std::string text = "";

        std::size_t length = fileLength(filePath);
        std::size_t it = 0;

        result.push_back("{\n");

        while (std::getline(file, text) && it < length) {

            if (text.empty() || it == 0 || it == length - 1)
            {
                ++it;
                continue;
            }

            if (std::regex_match(text, multilevel_prop_check) && it < length)
            {
                int braces_count = 1;
                
                std::string temp;

                temp += (text + '\n');

                while (std::getline(file, text) && it < length)
                {
                    if (static_cast<int>(text.find('{')) != -1 || static_cast<int>(text.find('[')) != -1)
                        ++braces_count;

                    else if (static_cast<int>(text.find('}')) != -1 || static_cast<int>(text.find(']')) != -1)
                        --braces_count;

                    if (braces_count == 0)
                    {
                        ++it;
                        temp += (text + '\n');
                        break;
                    }
                    temp += (text + '\n');
                    ++it;
                }
                result.push_back(temp);
                temp = "";
            }
            else if (!std::regex_match(text, multilevel_prop_check) && it < length)
                result.push_back(text + '\n');

            ++it;
        }

        result.push_back("}\n");

        file.close();
    }

    return result;
}


void printParsedJSON(const std::vector<std::string>& parsedJSON)
{
    for (int i = 0; i < parsedJSON.size(); ++i)
        std::cout << i + 1 << " " << parsedJSON[i];
}

std::pair<std::string, std::variant<double, bool, std::nullptr_t, std::string>> convertValue(const std::string& jsonStr)
{
    std::pair<std::string, std::variant<double, bool, std::nullptr_t, std::string>> result;

    std::regex propertyValue("\\s*\"([a-zA-Z0-9_-]+)\"\\s*:\\s*(\"[^\"]*\"|[^,\\n]*)\\s*(?:,|\\n|$)");

    std::regex isNumVal("^-?\\d+(\\.\\d+)?$");

    std::smatch propVal;

    std::regex_search(jsonStr, propVal, propertyValue);

    if (!propVal.empty() && propVal.size() == 3)
    {
        result.first = propVal[1]; // getting propName of JSON property
        
        std::string secondPropVal = propVal[2].str();

        // getting value of JSON property

        if (secondPropVal == "true")
            result.second = true;
        else if (secondPropVal == "false")
            result.second = false;
        else if (secondPropVal == "null")
            result.second = nullptr;
        else if (std::regex_match(secondPropVal, isNumVal))
            result.second = std::stod(secondPropVal);
        else
            result.second = secondPropVal;

        return result;
    }
    result.first = "";
    result.second = nullptr;

    return result;
}

/*

Explanation of the Regex: propertyValue

1. ( \"([a-zA-Z0-9_-]+)\" ) ->
    Captures the property name inside double quotes. Example: "key" matches and captures key.

2. ( :\" ) ->
    Matches the colon (:) separating the key and value.

3. ( (\"[^\"]*\"|[^,\\n]*) ) ->

    Matches:
    A quoted string: ( "[^"]*" ) (anything inside double quotes), or
    An unquoted value: ( [^,\\n]* ) (everything up to the next comma or newline).
    This ensures that commas inside quotes are preserved as part of the value.


4. ( \\s*(?:,|\\n|$) ) ->

    Matches optional trailing whitespace followed by:
    A comma (,) or
    A newline (\n) or
    The end of the string ($).

*/



std::map<std::string, std::variant<double, bool, std::nullptr_t, std::string>> parseJSON(const std::vector<std::string>& jsonStr)
{
    std::regex multilevel_prop_check("\\s*\"([a-zA-Z0-9_-]+)\"\\s*[:](.*)[,]\n");

    std::map<std::string, std::variant<double, bool, std::nullptr_t, std::string>> result;

    for (int i = 1; i < jsonStr.size() - 1; ++i)
    {
        if (std::regex_match(jsonStr[i], multilevel_prop_check))
        {
            std::pair<std::string, std::variant<double, bool, std::nullptr_t, std::string>> temp = convertValue(jsonStr[i]);
            result.insert(temp);
        }
    }

    return result;
}