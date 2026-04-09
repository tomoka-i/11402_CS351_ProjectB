# Project B — CSV Mini Database & Query Engine

## Overview

Build a compact, teachable CSV mini-database and query engine that ingests CSV files, builds lightweight indexes, and executes a simple query grammar for fast lookups and projections.

## Learning Goals

- **CSV parsing:** Understand common CSV formats (commas, quoted fields, escapes, embedded newlines) and either implement a simple robust parser or integrate a small library.  
- **Indexing:** Design lightweight indexes (column → row list, hash indexes, optional sorted indexes) to accelerate equality and range queries.  
- **Query grammar:** Implement a minimal query language supporting `SELECT`-style projection, predicates (equals, range), and logical `AND`/`OR`.  
- **Performance trade-offs:** Explore memory vs. latency, eager vs. lazy parsing, index-build cost vs. query speed, and when table scans beat indexed lookups.

## CSV Parsing Options

- **Write your own parser:** A teaching-focused parser that correctly handles quoted fields, embedded commas/newlines, and escaping. Minimal dependencies; full control for demonstrations.  
- **Use a lightweight library (optional):** Use a vetted CSV parser via `vcpkg` or `Conan` to focus effort on indexing and query execution.

## Implementation Notes

- Provide a CLI or small library API to: load a CSV, build indexes, run queries, and return results.  
- Index choices: per-column hash maps for equality, optional sorted arrays for range queries, or composite indexes for common multi-column predicates.  
- Query planner (optional): choose between index lookup and full scan based on selectivity estimates.

## Deliverables

- A working engine (CLI or API) that loads CSVs, builds indexes, and runs queries.  
- `README.md` with usage and design notes.  
- Example datasets and queries demonstrating parsing edge cases and performance trade-offs.  
- Unit tests or small benchmarks showing scan vs index performance (optional extras: persistent index export, simple aggregations).

## Getting Started

1. Place a CSV file in the project directory.  
2. Run the loader to build indexes and start the query REPL or execute a single query.  

Examples and commands will depend on your chosen language/tooling; if you want, I can scaffold a starter repo (C++ with `vcpkg`, Python, or Rust) and add a small CLI and tests.

---

For details, see this file: [README.md](README.md)
