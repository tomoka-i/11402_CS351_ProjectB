#include "CSVParser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

// simple split
static std::vector<std::string> split_csv_line(const std::string& line) {
    std::vector<std::string> result;
    std::string current;
    bool in_quotes = false;
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            result.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    result.push_back(current);
    // trim carriage return if present
    if (!result.empty() && !result.back().empty() && result.back().back() == '\r') {
        result.back().pop_back();
    }
    return result;
}

CSVTable CSVParser::parse(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("File Not Found: " + file_path);
    }

    CSVTable table;
    std::string line;
    
    // Read header
    if (std::getline(file, line)) {
        table.headers = split_csv_line(line);
    } else {
        return table; // empty file
    }

    // Read rows
    while (std::getline(file, line)) {
        if (line.empty() || line == "\r") continue;
        table.rows.push_back(split_csv_line(line));
    }

    return table;
}
