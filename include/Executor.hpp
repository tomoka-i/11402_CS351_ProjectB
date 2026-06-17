#pragma once
#include "Query.hpp"
#include "CSVParser.hpp"
#include "Indexer.hpp"
#include <iostream>
#include <unordered_map>
#include <memory>

class Executor {
public:
    void execute(const Query& query, std::ostream& out = std::cout);

private:
    // Simple cache of loaded files
    std::unordered_map<std::string, std::unique_ptr<CSVTable>> loaded_tables_;
    std::unordered_map<std::string, std::unique_ptr<Indexer>> table_indexers_;
    
    void load_table_if_needed(const std::string& file_name);
};
