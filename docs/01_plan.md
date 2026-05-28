# 01 Implementation Plan

## 1. CSV Parsing Strategy Decision
For this project, we must decide between implementing a custom CSV parser or using a third-party library via a package manager like `vcpkg` or `Conan`.

**Decision:** We will implement a **custom, lightweight CSV parser**.
**Rationale:** 
Since the primary goal of this mini-database is educational (focusing on understanding parsing, indexing, and execution from scratch), writing a custom parser maximizes the learning outcome. It also keeps the project dependency-free for its core functionality, simplifying the build process. The parser will handle standard commas and basic unquoted fields initially, with potential to extend to quoted fields if time permits.

## 2. Development Milestones
The project is divided into the following sequential milestones:

- **Milestone 1: Project Setup & Core Structures (Day 1)**
  - Scaffold CMake project.
  - Define core data structures (Row, Table, Query).
- **Milestone 2: Data Ingestion & Indexing (Day 2)**
  - Implement the custom CSV parser.
  - Implement the `std::unordered_map` based Indexer for O(1) equality lookups.
- **Milestone 3: Query Lexing & Parsing (Day 3)**
  - Implement the Lexer to tokenize the supported SQL subset.
  - Implement the Parser to validate syntax and generate the `Query` object.
- **Milestone 4: Execution & CLI (Day 4)**
  - Implement the Executor to fetch indexed rows and project columns.
  - Build the interactive CLI loop.
- **Milestone 5: Testing & Refinement (Day 5)**
  - Integrate Google Test.
  - Write unit and integration tests.
  - Configure GitHub Actions for CI.

## 3. Work Breakdown Structure (WBS)
1. **Infrastructure**
   1.1 Create `CMakeLists.txt`
   1.2 Setup Google Test via FetchContent
   1.3 Setup `.github/workflows/ci.yml`
2. **Core Implementation**
   2.1 `csv_parser.cpp`: Read file, split by delimiter, handle newlines.
   2.2 `indexer.cpp`: Map string values to `std::vector<size_t>` row IDs.
   2.3 `lexer.cpp`: String splitting and keyword matching.
   2.4 `executor.cpp`: Table lookups and string formatting for output.
   2.5 `main.cpp`: REPL loop and user prompt.
3. **Quality Assurance**
   3.1 Unit tests for Lexer.
   3.2 Unit tests for Indexer mapping correctness.
   3.3 Acceptance testing via shell scripts or E2E tests.
