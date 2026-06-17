#include "Executor.hpp"
#include <stdexcept>
#include <algorithm>

void Executor::load_table_if_needed(const std::string& file_name) {
    if (loaded_tables_.find(file_name) == loaded_tables_.end()) {
        try {
            auto table = std::make_unique<CSVTable>(CSVParser::parse(file_name));
            auto indexer = std::make_unique<Indexer>(*table);
            loaded_tables_[file_name] = std::move(table);
            table_indexers_[file_name] = std::move(indexer);
        } catch (const std::exception& e) {
            throw std::runtime_error(std::string("Error loading table: ") + e.what());
        }
    }
}

void Executor::execute(const Query& query, std::ostream& out) {
    try {
        load_table_if_needed(query.file_name);
    } catch (const std::exception& e) {
        out << e.what() << "\n";
        return;
    }

    const CSVTable& table = *loaded_tables_[query.file_name];
    Indexer& indexer = *table_indexers_[query.file_name];

    // Resolve column indices for selection
    std::vector<int> select_indices;
    std::vector<std::string> display_headers;

    if (query.select_all) {
        for (size_t i = 0; i < table.headers.size(); ++i) {
            select_indices.push_back(static_cast<int>(i));
            display_headers.push_back(table.headers[i]);
        }
    } else {
        for (const auto& col : query.select_columns) {
            auto it = std::find(table.headers.begin(), table.headers.end(), col);
            if (it == table.headers.end()) {
                out << "Error: Unknown Column: " << col << "\n";
                return;
            }
            select_indices.push_back(static_cast<int>(std::distance(table.headers.begin(), it)));
            display_headers.push_back(col);
        }
    }

    // Print headers
    for (size_t i = 0; i < display_headers.size(); ++i) {
        out << display_headers[i] << (i + 1 == display_headers.size() ? "" : ",");
    }
    out << "\n";

    // Handle WHERE clause or full scan
    if (query.where_column.empty()) {
        // No WHERE clause, full table scan
        for (const auto& row : table.rows) {
            for (size_t i = 0; i < select_indices.size(); ++i) {
                int col_idx = select_indices[i];
                if (col_idx < row.size()) {
                    out << row[col_idx];
                }
                out << (i + 1 == select_indices.size() ? "" : ",");
            }
            out << "\n";
        }
    } else {
        // Check if WHERE column exists
        auto it = std::find(table.headers.begin(), table.headers.end(), query.where_column);
        if (it == table.headers.end()) {
            out << "Error: Unknown Column: " << query.where_column << "\n";
            return;
        }

        // Use Index
        try {
            indexer.build_index(query.where_column);
            std::vector<size_t> row_indices = indexer.lookup(query.where_column, query.where_value);

            for (size_t row_idx : row_indices) {
                const auto& row = table.rows[row_idx];
                for (size_t i = 0; i < select_indices.size(); ++i) {
                    int col_idx = select_indices[i];
                    if (col_idx < row.size()) {
                        out << row[col_idx];
                    }
                    out << (i + 1 == select_indices.size() ? "" : ",");
                }
                out << "\n";
            }
        } catch (const std::exception& e) {
            out << "Error executing query: " << e.what() << "\n";
        }
    }
}
