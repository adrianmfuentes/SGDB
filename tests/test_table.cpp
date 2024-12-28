#include <gtest/gtest.h>
#include "table.h"

// Test case: Create a valid table
TEST(TableTest, CreateValidTable) {
    std::vector<std::string> columns = {"id", "name"};
    Table table("users", columns);

    EXPECT_EQ(table.getName(), "users");
    EXPECT_EQ(table.getColumnCount(), 2);
    EXPECT_EQ(table.getColumn(0), "id");
    EXPECT_EQ(table.getColumn(1), "name");
}

// Test case: Try to insert valid rows
TEST(TableTest, InsertValidRow) {
    std::vector<std::string> columns = {"id", "name"};
    Table table("users", columns);

    std::vector<std::string> row = {"1", "Alice"};
    table.insert(row);

    EXPECT_EQ(table.getRowCount(), 1);
    EXPECT_EQ(table.getRow(0)[0], "1");
    EXPECT_EQ(table.getRow(0)[1], "Alice");
}

// Test case: Try to insert a row with an invalid number of columns
TEST(TableTest, InsertRowWithWrongColumnCount) {
    std::vector<std::string> columns = {"id", "name"};
    Table table("users", columns);

    std::vector<std::string> row = {"1"};  // Missing column "name"
    table.insert(row);

    EXPECT_EQ(table.getRowCount(), 0);  // Should not be inserted
}

// Test case: Try to insert an empty row
TEST(TableTest, InsertEmptyRow) {
    std::vector<std::string> columns = {"id", "name"};
    Table table("users", columns);

    std::vector<std::string> row = {}; 
    table.insert(row);

    EXPECT_EQ(table.getRowCount(), 0);  // Should not be inserted
}

// Test case: Try to insert a row with empty columns 
TEST(TableTest, InsertRowWithEmptyColumn) {
    std::vector<std::string> columns = {"id", "name"};
    Table table("users", columns);

    std::vector<std::string> row = {"1", ""};  
    table.insert(row);

    EXPECT_EQ(table.getRowCount(), 1);
    EXPECT_EQ(table.getRow(0)[1], "");  // The empty column should be inserted
}

// Test case: Try to print a table
TEST(TableTest, PrintTable) {
    std::vector<std::string> columns = {"id", "name"};
    Table table("users", columns);

    std::vector<std::string> row1 = {"1", "Alice"};
    std::vector<std::string> row2 = {"2", "Bob"};
    table.insert(row1);
    table.insert(row2);

    testing::internal::CaptureStdout();
    table.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("id"), std::string::npos);
    EXPECT_NE(output.find("Alice"), std::string::npos);
    EXPECT_NE(output.find("Bob"), std::string::npos);
}
