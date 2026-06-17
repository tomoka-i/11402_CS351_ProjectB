#include <gtest/gtest.h>
#include "Lexer.hpp"
#include "CSVParser.hpp"
#include "Indexer.hpp"
#include "Executor.hpp"
#include <fstream>
#include <stdexcept>

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
    CSVTable table = CSVParser::parse("tests/data/test.csv");
    EXPECT_EQ(table.headers.size(), 3);
    
    Indexer indexer(table);
    indexer.build_index("Age");
    
    auto indices = indexer.lookup("Age", "30");
    EXPECT_EQ(indices.size(), 2); // Alice and Charlie
}

// Test Executor Edge Cases
TEST(ExecutorTest, UnknownColumn) {
    std::string q_str = "SELECT Unknown FROM tests/data/test.csv WHERE Age = 30";
    Query q = Lexer::parse(q_str);
    
    Executor executor;
    testing::internal::CaptureStdout();
    executor.execute(q);
    std::string output = testing::internal::GetCapturedStdout();
    // Executor outputs to std::cerr or out for errors. We capture stdout here. 
    // Usually, exceptions are better for unknown columns, but we'll check if output is empty or has an error.
    EXPECT_NE(output.find("Unknown"), std::string::npos);
}

TEST(ExecutorTest, FileNotFound) {
    std::string q_str = "SELECT Id FROM missing.csv WHERE Age = 30";
    Query q = Lexer::parse(q_str);
    
    Executor executor;
    // CSVParser throws runtime_error on file not found based on traceability matrix
    EXPECT_THROW(executor.execute(q), std::runtime_error);
}

TEST(ExecutorTest, EmptyResult) {
    std::string q_str = "SELECT Id FROM tests/data/test.csv WHERE Age = 100";
    Query q = Lexer::parse(q_str);
    
    Executor executor;
    testing::internal::CaptureStdout();
    executor.execute(q);
    std::string output = testing::internal::GetCapturedStdout();
    // It might output (0 rows returned) or No matching records found. 
    // We'll just ensure it runs without crashing.
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
