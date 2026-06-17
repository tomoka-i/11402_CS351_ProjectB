#include "Lexer.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

// Helper to trim whitespace from ends of a string
static std::string trim(const std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        start++;
    }
    auto end = s.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    
    return std::string(start, end + 1);
}

// Helper to check prefix
static bool starts_with_ignore_case(const std::string& str, const std::string& prefix) {
    if (str.length() < prefix.length()) return false;
    for (size_t i = 0; i < prefix.length(); ++i) {
        if (std::tolower(str[i]) != std::tolower(prefix[i])) {
            return false;
        }
    }
    return true;
}

Query Lexer::parse(const std::string& query_string) {
    Query q;
    std::string s = trim(query_string);
    if (!s.empty() && s.back() == ';') {
        s.pop_back();
        s = trim(s);
    }

    if (!starts_with_ignore_case(s, "SELECT ")) {
        throw std::invalid_argument("Syntax Error: Query must start with SELECT");
    }
    s = trim(s.substr(7)); // remove "SELECT "

    size_t from_pos = s.find(" FROM ");
    if (from_pos == std::string::npos) {
        from_pos = s.find(" from ");
    }
    if (from_pos == std::string::npos) {
        throw std::invalid_argument("Syntax Error: Missing FROM clause");
    }

    std::string cols_part = trim(s.substr(0, from_pos));
    s = trim(s.substr(from_pos + 6)); // remove " FROM "

    if (cols_part == "*") {
        q.select_all = true;
    } else {
        std::stringstream ss(cols_part);
        std::string col;
        while (std::getline(ss, col, ',')) {
            q.select_columns.push_back(trim(col));
        }
    }

    size_t where_pos = s.find(" WHERE ");
    if (where_pos == std::string::npos) {
        where_pos = s.find(" where ");
    }

    if (where_pos == std::string::npos) {
        q.file_name = trim(s); // No WHERE clause
        return q;
    }

    q.file_name = trim(s.substr(0, where_pos));
    s = trim(s.substr(where_pos + 7)); // remove " WHERE "

    size_t eq_pos = s.find('=');
    if (eq_pos == std::string::npos) {
        throw std::invalid_argument("Syntax Error: WHERE clause missing '='");
    }

    q.where_column = trim(s.substr(0, eq_pos));
    q.where_value = trim(s.substr(eq_pos + 1));
    
    // basic handling of optional quotes in value
    if (q.where_value.size() >= 2 && 
        ((q.where_value.front() == '\'' && q.where_value.back() == '\'') ||
         (q.where_value.front() == '"' && q.where_value.back() == '"'))) {
        q.where_value = q.where_value.substr(1, q.where_value.size() - 2);
    }

    return q;
}
