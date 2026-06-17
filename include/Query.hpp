#pragma once
#include <string>
#include <vector>

struct Query {
    std::vector<std::string> select_columns;
    std::string file_name;
    std::string where_column;
    std::string where_value;
    bool select_all = false;
};
