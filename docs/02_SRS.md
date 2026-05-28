# 02 Software Requirements Specification (SRS)

## 1. Introduction
This document specifies the software requirements for the CSV Mini Database & Query Engine, focusing on the query syntax, functional requirements, and non-functional requirements.

## 2. Supported Query Syntax
The system shall support a specific, simplified subset of SQL for querying CSV data. The supported pattern is strictly:

`SELECT [column_names] FROM [file_name] WHERE [target_column] = [value];`

- `[column_names]`: A comma-separated list of column headers to project (e.g., `id, name, age`) or `*` for all columns.
- `[file_name]`: The path or name of the target CSV file.
- `[target_column]`: The column to apply the predicate on.
- `[value]`: The exact value to match (equality check).

## 3. Functional Requirements
- **FR1. CSV Ingestion:** The system must read and parse standard CSV files, correctly handling headers, commas, and simple fields.
- **FR2. Index Generation:** The system shall automatically build an in-memory index for the columns to facilitate fast equality lookups.
- **FR3. Query Parsing:** The system must parse the specified `SELECT` query string and extract the projection list, target table/file, and WHERE clause conditions.
- **FR4. Query Execution:** The system must execute the parsed query using the generated indexes and return the matching rows with only the requested columns.
- **FR5. Error Handling:** 
  - If a file cannot be found or read, the system shall output an appropriate error message.
  - If a syntax error occurs in the query, the system must report "Syntax Error" and point out the malformed section.
  - If a requested column in `SELECT` or `WHERE` does not exist in the CSV, the system shall return an "Unknown Column" error.

## 4. Non-Functional Requirements
- **NFR1. Performance:** Queries leveraging the index (equality matching) should resolve in O(1) average time complexity regarding the search operation.
- **NFR2. Usability:** The CLI must be intuitive, providing clear prompts and readable error messages.
- **NFR3. Portability:** The engine should be written in standard C++ and rely on minimal external dependencies for core functionality.
