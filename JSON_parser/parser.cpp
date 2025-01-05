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

std::vector<std::string> parseJSON(const std::string& filePath)
{
    std::vector<std::string> result;

    std::ifstream file(filePath);

    std::regex multi_property("\\s*\"([a-zA-Z0-9_-]+)\"\\s*[\:]\\s*(([\[])|([\{]))\\s*");

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

            if (std::regex_match(text, multi_property) && it < length)
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
            else if (!std::regex_match(text, multi_property) && it < length)
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
