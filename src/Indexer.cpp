#include "Indexer.hpp"
#include <stdexcept>

Indexer::Indexer(const CSVTable& table) : table_(table) {}

int Indexer::get_column_index(const std::string& column_name) const {
    for (size_t i = 0; i < table_.headers.size(); ++i) {
        if (table_.headers[i] == column_name) {
            return i;
        }
    }
    return -1;
}

void Indexer::build_index(const std::string& column_name) {
    if (indexes_.find(column_name) != indexes_.end()) {
        return; // Already indexed
    }

    int col_idx = get_column_index(column_name);
    if (col_idx == -1) {
        throw std::invalid_argument("Unknown Column: " + column_name);
    }

    std::unordered_map<std::string, std::vector<size_t>> column_index;
    for (size_t i = 0; i < table_.rows.size(); ++i) {
        if (col_idx < table_.rows[i].size()) {
            column_index[table_.rows[i][col_idx]].push_back(i);
        }
    }
    indexes_[column_name] = std::move(column_index);
}

std::vector<size_t> Indexer::lookup(const std::string& column_name, const std::string& value) const {
    auto it = indexes_.find(column_name);
    if (it == indexes_.end()) {
        throw std::invalid_argument("Column not indexed: " + column_name);
    }

    auto val_it = it->second.find(value);
    if (val_it != it->second.end()) {
        return val_it->second;
    }
    
    return {}; // No matches
}
