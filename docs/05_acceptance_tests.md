# 05 Acceptance Tests

## 1. Prerequisites
For all tests below, assume the file `data/Iris Data.csv` exists in the working directory. The dataset contains columns such as: `Id,SepalLengthCm,SepalWidthCm,PetalLengthCm,PetalWidthCm,Species`.

## 2. Test Cases

### TC1: Normal SELECT Projection (All rows, specific columns)
- **Input Query:** `SELECT Id, Species FROM data/Iris Data.csv WHERE SepalLengthCm = 5.1;`
- **Expected Output:**
  ```text
  Id, Species
  1, Iris-setosa
  ... (and other matching rows)
  ```
- **Pass Criteria:** Only the requested columns are printed, and only for rows where `SepalLengthCm` is exactly `5.1`.

### TC2: Normal SELECT Projection (All columns)
- **Input Query:** `SELECT * FROM data/Iris Data.csv WHERE Id = 2;`
- **Expected Output:**
  ```text
  Id, SepalLengthCm, SepalWidthCm, PetalLengthCm, PetalWidthCm, Species
  2, 4.9, 3.0, 1.4, 0.2, Iris-setosa
  ```
- **Pass Criteria:** All columns from the original file are printed for the matched row.

### TC3: Empty Result Set
- **Input Query:** `SELECT Id FROM data/Iris Data.csv WHERE Species = Iris-unknown;`
- **Expected Output:**
  ```text
  (0 rows returned)
  ```
- **Pass Criteria:** The system gracefully handles cache misses in the index map and outputs an empty result indicator.

### TC4: Syntax Error Handling
- **Input Query:** `SELECT Species FROM data/Iris Data.csv SepalLengthCm = 5.1;` (Missing WHERE)
- **Expected Output:** 
  ```text
  Error: Syntax Error. Expected 'WHERE' keyword.
  ```
- **Pass Criteria:** The Lexer detects the malformed query, aborts execution safely, and provides a readable error.

### TC5: Unknown Column Error
- **Input Query:** `SELECT Color FROM data/Iris Data.csv WHERE Id = 1;`
- **Expected Output:**
  ```text
  Error: Unknown Column 'Color'
  ```
- **Pass Criteria:** The Executor detects that the projected column does not exist in the parsed CSV header and returns an error.

### TC6: File Not Found Error
- **Input Query:** `SELECT * FROM data/missing.csv WHERE Id = 1;`
- **Expected Output:**
  ```text
  Error: Cannot open file 'data/missing.csv'
  ```
- **Pass Criteria:** The Indexer safely fails and propagates the file I/O error to the CLI.
