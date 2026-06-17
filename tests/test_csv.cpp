#include <gtest/gtest.h>
#include "Lexer.hpp"
#include "CSVParser.hpp"
#include "Indexer.hpp"
#include "Executor.hpp"
#include <fstream>
#include <stdexcept>
#include <sstream>

// Helper to resolve test file paths regardless of the working directory
std::string get_test_file_path(const std::string& filename) {
    // Try current directory
    std::ifstream f1(filename);
    if (f1.good()) return filename;

    // Try relative to build dir
    std::string rel_path = "../" + filename;
    std::ifstream f2(rel_path);
    if (f2.good()) return rel_path;
    
    return filename; // fallback
}

// Test Lexer
TEST(LexerTest, ValidQuery) {
    std::string q_str = "SELECT Id, Name FROM tests/data/test.csv WHERE Age = 30";
    Query q = Lexer::parse(q_str);
    
    EXPECT_EQ(q.select_columns.size(), 2);
    EXPECT_EQ(q.select_columns[0], "Id");
    EXPECT_EQ(q.select_columns[1], "Name");
    EXPECT_EQ(q.file_name, "tests/data/test.csv");
    EXPECT_EQ(q.where_column, "Age");
    EXPECT_EQ(q.where_value, "30");
}

TEST(LexerTest, SelectAll) {
    std::string q_str = "SELECT * FROM tests/data/test.csv WHERE Age = 30";
    Query q = Lexer::parse(q_str);
    
    EXPECT_TRUE(q.select_all);
    EXPECT_EQ(q.file_name, "tests/data/test.csv");
}

TEST(LexerTest, MissingFrom) {
    std::string q_str = "SELECT Id, Name tests/data/test.csv WHERE Age = 30";
    EXPECT_THROW(Lexer::parse(q_str), std::invalid_argument); // Traceability says std::invalid_argument
}

// Test CSVParser & Indexer
TEST(IndexerTest, BuildIndex) {
    std::string path = get_test_file_path("tests/data/test.csv");
    CSVTable table = CSVParser::parse(path);
    EXPECT_EQ(table.headers.size(), 3);
    
    Indexer indexer(table);
    indexer.build_index("Age");
    
    auto indices = indexer.lookup("Age", "30");
    EXPECT_EQ(indices.size(), 2); // Alice and Charlie
}

// Test Executor Edge Cases
TEST(ExecutorTest, UnknownColumn) {
    std::string path = get_test_file_path("tests/data/test.csv");
    std::string q_str = "SELECT Unknown FROM " + path + " WHERE Age = 30";
    Query q = Lexer::parse(q_str);
    
    Executor executor;
    std::stringstream ss;
    executor.execute(q, ss);
    std::string output = ss.str();
    
    // Executor writes error string directly to stream for unknown column
    EXPECT_NE(output.find("Error: Unknown Column"), std::string::npos);
}

TEST(ExecutorTest, FileNotFound) {
    std::string q_str = "SELECT Id FROM missing.csv WHERE Age = 30";
    Query q = Lexer::parse(q_str);
    
    Executor executor;
    std::stringstream ss;
    executor.execute(q, ss);
    std::string output = ss.str();

    // Executor catches the CSVParser std::runtime_error and writes it to stream
    EXPECT_NE(output.find("Error loading table: File Not Found: missing.csv"), std::string::npos);
}

TEST(ExecutorTest, EmptyResult) {
    std::string path = get_test_file_path("tests/data/test.csv");
    std::string q_str = "SELECT Id FROM " + path + " WHERE Age = 100";
    Query q = Lexer::parse(q_str);
    
    Executor executor;
    std::stringstream ss;
    executor.execute(q, ss);
    std::string output = ss.str();
    // Headers are still printed, but no rows. As long as it doesn't crash, it's fine.
    EXPECT_NE(output.find("Id"), std::string::npos); 
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
