# 03 Software Design Specification (SDS)

## 1. Architecture Overview
The CSV Mini Database is built using a modular architecture consisting of four primary components: CLI, Lexer (Parser), Indexer, and Executor. This separation of concerns ensures that parsing the query, indexing the data, and executing the search are decoupled and maintainable.

## 2. Module Descriptions

### 2.1 CLI (Command Line Interface)
- **Role:** The entry point of the application. It handles user input (the query string) and orchestrates the other modules.
- **Responsibilities:**
  - Read queries from standard input.
  - Pass the query to the Lexer.
  - Pass the parsed query structure to the Executor.
  - Format and print the final results or error messages to standard output.

### 2.2 Lexer / Parser
- **Role:** Transforms the raw SQL-like query string into a structured, executable format.
- **Responsibilities:**
  - Tokenize the input string (`SELECT`, column names, `FROM`, file name, `WHERE`, target column, `=`, value).
  - Validate the syntax against the supported pattern.
  - Output an internal `Query` struct containing:
    - `std::vector<std::string> select_columns`
    - `std::string file_name`
    - `std::string where_column`
    - `std::string where_value`

### 2.3 Indexer
- **Role:** Loads the CSV data into memory and builds the necessary data structures for fast querying.
- **Responsibilities:**
  - Parse the CSV file and store the raw rows (e.g., `std::vector<std::vector<std::string>>`).
  - Construct an index using `std::unordered_map`.
  - **Data Structure:** For a specific column, the index maps a column value to a list of row indices. 
    - Type: `std::unordered_map<std::string, std::vector<size_t>>`
    - Key: The string value from the cell.
    - Value: A vector of row numbers where this value appears.

### 2.4 Executor
- **Role:** Takes the structured `Query` and the in-memory data/indexes, and produces the result set.
- **Responsibilities:**
  - Identify the target file and request the Indexer to load/index it if not already done.
  - Look up the `where_value` in the `std::unordered_map` corresponding to the `where_column`.
  - Retrieve the vector of matching row indices in O(1) average time.
  - Iterate through the matching row indices, project only the `select_columns`, and format the output.

## 3. Data Flow
1. User inputs: `SELECT name, age FROM users.csv WHERE city = Tokyo;`
2. **CLI** captures the string and sends it to the **Lexer**.
3. **Lexer** returns a `Query` object: `{select: ["name", "age"], from: "users.csv", where_col: "city", where_val: "Tokyo"}`.
4. **CLI** passes the `Query` object to the **Executor**.
5. **Executor** checks if `users.csv` is loaded. If not, the **Indexer** reads the file and builds a `std::unordered_map` for the `city` column.
6. **Executor** queries the map: `index["Tokyo"]`, getting row IDs (e.g., `[2, 5, 8]`).
7. **Executor** fetches rows `2, 5, 8`, extracts the `name` and `age` fields, and returns the result to the **CLI**.
8. **CLI** prints the tabular result to the screen.
