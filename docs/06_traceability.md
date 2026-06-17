# 06 Traceability Matrix

This document maps the requirements defined in the Software Requirements Specification (SRS) to the specific source code files and functions that implement them.

| Requirement ID | Description | Implemented In (File) | Function / Component |
|---|---|---|---|
| **FR1** | CSV Ingestion (read and parse CSV files) | `src/CSVParser.cpp` | `CSVParser::parse`, `split_csv_line` |
| **FR2** | Index Generation (build hash index) | `src/Indexer.cpp` | `Indexer::build_index`, `Indexer::lookup` |
| **FR3** | Query Parsing (`SELECT` statement) | `src/Lexer.cpp` | `Lexer::parse` |
| **FR4** | Query Execution (execute query, return rows) | `src/Executor.cpp` | `Executor::execute`, `Executor::load_table_if_needed` |
| **FR5** | Error Handling: File not found | `src/CSVParser.cpp` | `CSVParser::parse` (Throws `std::runtime_error`) |
| **FR5** | Error Handling: Syntax error | `src/Lexer.cpp` | `Lexer::parse` (Throws `std::invalid_argument`) |
| **FR5** | Error Handling: Unknown column | `src/Executor.cpp` <br> `src/Indexer.cpp` | `Executor::execute`, `Indexer::build_index` |
