#pragma once
#include <string>
#include <vector>

struct CSVTable {
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> rows;
};

class CSVParser {
public:
    static CSVTable parse(const std::string& file_path);
};
