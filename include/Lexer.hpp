#pragma once
#include "Query.hpp"
#include <string>
#include <stdexcept>

class Lexer {
public:
    static Query parse(const std::string& query_string);
};
