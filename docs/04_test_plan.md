# 04 Test Plan

## 1. Testing Framework
We will use **Google Test (gtest)** as the primary testing framework for unit and integration testing. It is the industry standard for C++, provides rich assertion macros, and integrates easily with CMake via `FetchContent` or standard module inclusion.

## 2. Unit Testing Strategy
Unit tests will target individual modules in isolation to ensure their internal logic is sound.

- **Lexer/Parser Tests:**
  - Verify that valid query strings are parsed into the correct `Query` struct fields.
  - Verify that invalid queries (e.g., typos in `SELECT`, missing `FROM`) throw the expected syntax exceptions.
- **CSV Parser Tests:**
  - Test with perfectly formatted CSV files.
  - Test with missing values/empty fields.
  - Test with trailing newlines.
- **Indexer Tests:**
  - Verify that indexing a known dataset produces the correct mapping in the `std::unordered_map`.
  - Verify that retrieving row IDs for a specific value returns the exact matching set.

## 3. Integration Testing Strategy
Integration tests will verify the interaction between the Parser, Indexer, and Executor.
- We will construct an in-memory testing environment where a string query is passed in, and the final output buffer (simulating `stdout`) is compared against an expected string.

## 4. Test Execution
- Tests will be executed locally via `ctest` in the CMake build directory.
- Tests will be executed automatically on every push and pull request via GitHub Actions (CI).
