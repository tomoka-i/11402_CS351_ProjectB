# 08 Known Issues and Limitations

This document records technical limitations, known bugs, and constraints identified during the implementation phase.

## Current Limitations

1. **Memory Constraints (Large CSV Files)**: 
   - The current implementation of `CSVParser` and `Indexer` loads the entire dataset into memory at once (`CSVTable`).
   - Because of this memory architecture, attempting to load extremely large CSV files (e.g., 10 million rows or more) will likely exceed available RAM and cause an out-of-memory exception.

2. **Parsing Rigidity (Whitespace & Formatting)**:
   - The query parser (`Lexer`) uses strict string searching (e.g., looking for ` FROM ` and ` WHERE `) instead of a fully-featured abstract syntax tree (AST).
   - This means extra spaces or uncommon formatting around clauses could break parsing, and nested queries or complex expressions are unsupported.

3. **CSV Parsing Edge Cases**:
   - Although double-quotes around fields are partially handled, the parser does not support embedded newlines within quoted fields, nor does it support escaped quotes (e.g., `""`) inside a quoted string.

4. **Data Types**:
   - All parsed data is strictly treated as strings. There is no type inference for integers or floats, meaning numeric range queries (like `<` or `>`) are not possible under the current index design. Only exact string match (equality check) is supported.
