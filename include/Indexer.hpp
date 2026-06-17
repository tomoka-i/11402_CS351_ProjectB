#pragma once
#include "CSVParser.hpp"
#include <unordered_map>
#include <string>
#include <vector>

class Indexer {
public:
    Indexer(const CSVTable& table);

    // Build index for a specific column
    void build_index(const std::string& column_name);

    // Retrieve row IDs for a given value
    std::vector<size_t> lookup(const std::string& column_name, const std::string& value) const;

private:
    const CSVTable& table_;
    // Map: Column Name -> (Map: Value -> Row Indices)
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<size_t>>> indexes_;
    
    int get_column_index(const std::string& column_name) const;
};
