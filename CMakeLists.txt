cmake_minimum_required(VERSION 3.14)
project(CSVDatabase CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(csv_db
    src/main.cpp
    src/Lexer.cpp
    src/CSVParser.cpp
    src/Indexer.cpp
    src/Executor.cpp
)

# Optional: Testing
# enable_testing()
# add_executable(test_csv tests/test_csv.cpp src/Lexer.cpp src/CSVParser.cpp src/Indexer.cpp src/Executor.cpp)
# add_test(NAME test_csv COMMAND test_csv)
