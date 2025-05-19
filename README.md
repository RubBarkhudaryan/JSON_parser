C++ JSON Parser

Overview
This small C++ project implements a lightweight JSON parser that reads a JSON file, extracts top-level properties, and exposes them as a std::map of key→value pairs. Values are stored in a std::variant\<double, bool, std::nullptr\_t, std::string>, so numeric, boolean, null, and string types are all supported seamlessly.

Key Features

* File-based input: Reads a JSON file line-by-line, handles nested objects/arrays by grouping them into single string entries for later parsing.
* Type inference: Automatically detects and converts JSON values to their native C++ types:

  * Floating-point and integer numbers → double
  * true / false → bool
  * null → nullptr\_t
  * Quoted text → std::string
* Regex-driven parsing: Uses std::regex to locate property names and values in each line, keeping the implementation concise.
* Modern C++: Leverages C++17 features—std::variant, std::visit, range-based loops, and smart header-only structure.

Project Structure

```
├── parser.h         # Declarations of parsing functions and utilities
├── parser.cpp       # Implementation: file reading, regex matching, type conversion
├── main.cpp         # Example driver: loads “data.json”, parses it, and prints key ⇒ value
└── data.json        # (Not included) JSON file to be parsed
```

How It Works

1. JSONToStringArr(filePath)
   Reads the file into a std::vector[std::string](std::string), merging multi-line nested objects/arrays into single entries so that each element of the vector corresponds to exactly one JSON property or value block.

2. parseJSON(stringArr)
   Iterates over the vector (skipping the opening “{” and closing “}”), applies a regex to each line to extract "<key>": <rawValue>, then calls convertValue to transform that raw value into the appropriate C++ type. Results are stored in a std::map\<std::string, std::variant<…>>.

3. main()

   * Calls JSONToStringArr("./data.json")
   * Parses with parseJSON(...)
   * Prints each property name and its value via std::visit.

Building & Running

```
g++ -std=c++17 main.cpp parser.cpp -o jsonparser
./jsonparser
```

*(Make sure data.json is in the same directory, or adjust the path in main.cpp.)*

Use Cases

* Quick parsing of simple, flat JSON configurations into C++ programs
* Educational example for modern C++ features (regex, variant, visit)
* Foundation for more advanced JSON handling (could be extended to full recursive parsing)
