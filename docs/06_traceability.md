# 06 Traceability Matrix

This document maps the requirements defined in the Software Requirements Specification (SRS) to the specific source code components and the automated test cases that verify them. This ensures that every requirement is implemented and proven to work.

| Requirement ID | Description | Implemented In (File) | Test Case ID / Name |
|---|---|---|---|
| **FR1** | CSV Ingestion (read and parse CSV files) | `src/CSVParser.cpp` | `IndexerTest.BuildIndex` (tests parsing during indexing) |
| **FR2** | Index Generation (build hash index) | `src/Indexer.cpp` | `IndexerTest.BuildIndex` |
| **FR3** | Query Parsing (`SELECT` statement) | `src/Lexer.cpp` | `LexerTest.ValidQuery`, `LexerTest.SelectAll`, `LexerTest.MissingFrom` |
| **FR4** | Query Execution (execute query, return rows) | `src/Executor.cpp` | `ExecutorTest.EmptyResult`, TC1, TC2 |
| **FR5** | Error Handling: File not found | `src/CSVParser.cpp` | `ExecutorTest.FileNotFound`, TC6 |
| **FR5** | Error Handling: Syntax error | `src/Lexer.cpp` | `LexerTest.MissingFrom`, TC4 |
| **FR5** | Error Handling: Unknown column | `src/Executor.cpp` | `ExecutorTest.UnknownColumn`, TC5 |