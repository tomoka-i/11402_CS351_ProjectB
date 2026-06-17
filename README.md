# Project B — CSV Mini Database & Query Engine

[![C++ CI with CMake](https://github.com/tomoka-i/11402_CS351_ProjectB/actions/workflows/ci.yml/badge.svg)](https://github.com/tomoka-i/11402_CS351_ProjectB/actions/workflows/ci.yml)

## Overview

A compact, teachable CSV mini-database and query engine implemented in C++. It ingests CSV files, builds lightweight hash indexes, and executes a simple `SELECT` query grammar for fast lookups and projections.

This project was built to demonstrate:
- Custom CSV parsing and data ingestion.
- In-memory data structures and indexing.
- Lexical analysis and query parsing.
- Automated testing via Google Test and GitHub Actions.

## Getting Started

### Prerequisites
- A C++17 compatible compiler
- CMake (version 3.14 or higher)

### Build Instructions

1. **Clone the repository and prepare the build directory:**
   ```bash
   mkdir build && cd build
   cmake ..
   ```

2. **Compile the project:**
   ```bash
   make
   ```
   This generates the main executable (`csv_db`) and the test executable (`test_csv`).

### Usage Example

Run the main application from the build directory. The CLI will prompt you to enter a query.

```bash
./csv_db
```

**Example Query:**
```sql
SELECT Id, Species FROM data/Iris Data.csv WHERE SepalLengthCm = 5.1
```

**Supported Query Syntax:**
```sql
SELECT <column1, column2... | *> FROM <filepath> WHERE <column> = <value>
```
*(Note: Range queries like `<` or `>` are not supported in this basic version; only exact string matching is supported.)*

### Running Tests

Unit and integration tests are powered by Google Test. You can run them via CTest:

```bash
cd build
ctest --output-on-failure
```

## Documentation

For deep dives into the architecture, design decisions, and testing strategies, please refer to the `docs/` folder:
- [Software Requirements (SRS)](docs/02_SRS.md)
- [System Design (SDS)](docs/03_SDS.md)
- [Test Plan & Traceability](docs/04_test_plan.md)
