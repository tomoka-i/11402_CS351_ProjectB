# 07 Deployment & Build Guide

## 1. Prerequisites
To build and run the CSV Mini Database, the following tools are required:
- A C++17 compatible compiler (e.g., GCC 8+, Clang 7+, MSVC 2019+)
- CMake (version 3.15 or higher)
- Make or Ninja build system

## 2. Local Build Instructions

The project uses CMake as its build system. Follow these steps to compile the application and the test suite:

1. **Clone the repository:**
   ```bash
   git clone <repository_url>
   cd 11402_CS351_ProjectB
   ```

2. **Generate build files:**
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. **Compile the project:**
   ```bash
   make
   ```
   *This will generate the main executable (e.g., `minidb`) and the test executable (e.g., `minidb_tests`).*

4. **Run the Tests:**
   ```bash
   ctest --output-on-failure
   ```

5. **Run the Application:**
   ```bash
   ./minidb
   ```

## 3. Continuous Integration (CI)
The project utilizes GitHub Actions to ensure code quality. The CI pipeline is defined in `.github/workflows/ci.yml`.

**CI Workflow Steps:**
1. **Trigger:** Runs on every `push` to the `main` branch and on every `pull_request`.
2. **Environment:** Runs on `ubuntu-latest`.
3. **Checkout:** Checks out the code.
4. **Configure:** Runs `cmake -B build -S .`
5. **Build:** Runs `cmake --build build`
6. **Test:** Runs `ctest --test-dir build --output-on-failure`

This ensures that any new commits do not break existing parsing, indexing, or query execution logic.
