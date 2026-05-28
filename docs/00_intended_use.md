# 00 Intended Use

## 1. Purpose
The CSV Mini Database & Query Engine is designed to be a compact, teaching-focused tool. Its primary purpose is to demonstrate fundamental database concepts such as file parsing, in-memory indexing, and query execution. It allows users to quickly search and project data from CSV files without the overhead of setting up a full-scale Relational Database Management System (RDBMS).

## 2. Target Audience
- **Students and Learners:** Individuals learning about database internals, indexing mechanisms, and query processing.
- **Developers and Researchers:** Users who need a lightweight, fast, and dependency-free way to query static CSV datasets using a familiar SQL-like syntax.

## 3. Scope and Usage Scenario
The system operates primarily in-memory. A typical usage scenario involves:
1. Providing a CSV file to the application.
2. The application reads the CSV and builds an in-memory index (e.g., using hash maps) for fast lookups.
3. The user inputs a simple `SELECT` query via the Command Line Interface (CLI).
4. The system parses the query, utilizes the index to quickly find matching rows, and outputs the requested columns.

The tool is not intended for transactional processing (OLTP) or handling datasets that exceed available system memory. It is optimized for read-heavy operations on static CSV data.
