#include <gtest/gtest.h>
#include "Lexer.hpp"
#include "CSVParser.hpp"
#include "Indexer.hpp"
#include "Executor.hpp"
#include <fstream>

// Test Lexer
TEST(LexerTest, ValidQuery) {
    std::string q_str = "SELECT Id, Name FROM tests/data/test.csv WHERE Age = 30";
    Lexer lexer(q_str);
    Query q = lexer.parse();
    
    EXPECT_EQ(q.columns.size(), 2);
    EXPECT_EQ(q.columns[0], "Id");
    EXPECT_EQ(q.columns[1], "Name");
    EXPECT_EQ(q.table, "tests/data/test.csv");
    EXPECT_EQ(q.whereColumn, "Age");
    EXPECT_EQ(q.whereValue, "30");
}

TEST(LexerTest, SelectAll) {
    std::string q_str = "SELECT * FROM tests/data/test.csv WHERE Age = 30";
    Lexer lexer(q_str);
    Query q = lexer.parse();
    
    EXPECT_TRUE(q.selectAll);
    EXPECT_EQ(q.table, "tests/data/test.csv");
}

TEST(LexerTest, MissingFrom) {
    std::string q_str = "SELECT Id, Name tests/data/test.csv WHERE Age = 30";
    Lexer lexer(q_str);
    EXPECT_THROW(lexer.parse(), std::runtime_error);
}

// Test CSVParser & Indexer
TEST(IndexerTest, BuildIndex) {
    CSVParser parser("tests/data/test.csv");
    auto header = parser.readHeader();
    EXPECT_EQ(header.size(), 3);
    
    Indexer indexer;
    indexer.buildIndex("tests/data/test.csv", "Age");
    
    auto indices = indexer.getIndices("30");
    EXPECT_EQ(indices.size(), 2); // Alice and Charlie
}

// Test Executor Edge Cases
TEST(ExecutorTest, UnknownColumn) {
    std::string q_str = "SELECT Unknown FROM tests/data/test.csv WHERE Age = 30";
    Lexer lexer(q_str);
    Query q = lexer.parse();
    
    Executor executor(q);
    testing::internal::CaptureStdout();
    executor.execute();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Error: Column not found"), std::string::npos);
}

TEST(ExecutorTest, FileNotFound) {
    std::string q_str = "SELECT Id FROM missing.csv WHERE Age = 30";
    Lexer lexer(q_str);
    Query q = lexer.parse();
    
    Executor executor(q);
    testing::internal::CaptureStdout();
    executor.execute();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Error: Cannot open file"), std::string::npos);
}

TEST(ExecutorTest, EmptyResult) {
    std::string q_str = "SELECT Id FROM tests/data/test.csv WHERE Age = 100";
    Lexer lexer(q_str);
    Query q = lexer.parse();
    
    Executor executor(q);
    testing::internal::CaptureStdout();
    executor.execute();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("No matching records found."), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
