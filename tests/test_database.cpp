#include <gtest/gtest.h>
#include "database.h"

// Test case: Create a valid table
TEST(DatabaseTest, CreateValidTable) {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    db.createTable("users", columns);

    // Verifica que la tabla ha sido creada correctamente
    EXPECT_EQ(db.getTableNames().size(), 1);
    EXPECT_EQ(db.getTableNames()[0], "users");
}

// Test case: Try to create a table with empty columns
TEST(DatabaseTest, CreateTableWithEmptyColumns) {
    Database db;
    std::vector<std::string> columns = {};  
    db.createTable("users", columns);

    // Verify that the table was not created due to empty columns
    EXPECT_EQ(db.getTableNames().size(), 0);
}

// Test case: Try to create a table with duplicate columns
TEST(DatabaseTest, CreateTableWithDuplicateColumns) {
    Database db;
    std::vector<std::string> columns = {"id", "name", "id"};  
    db.createTable("users", columns);

    // Verify that the table was not created due to duplicate columns
    EXPECT_EQ(db.getTableNames().size(), 0);
}

// Test case: Try to create a table with valid columns
TEST(DatabaseTest, InsertValidRow) {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    db.createTable("users", columns);

    std::vector<std::string> row = {"1", "Alice"};
    db.insertRow("users", row);

    // Verify that the row was inserted
    const Table& table = db.getTable("users");
    EXPECT_EQ(table.getRowCount(), 1);
    EXPECT_EQ(table.getRow(0)[0], "1");
    EXPECT_EQ(table.getRow(0)[1], "Alice");
}

// Test case: Try to insert a row with an invalid number of columns
TEST(DatabaseTest, InsertInvalidRow) {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    db.createTable("users", columns);

    std::vector<std::string> row = {"1"};  // Missing column
    db.insertRow("users", row);

    // Verify that the row was not inserted
    const Table& table = db.getTable("users");
    EXPECT_EQ(table.getRowCount(), 0);
}

// Test case: Try to insert a row in a nonexistent table
TEST(DatabaseTest, InsertRowInNonexistentTable) {
    Database db;
    std::vector<std::string> row = {"1", "Alice"};
    db.insertRow("users", row);

    // Verify that the row was not inserted
    EXPECT_EQ(db.getTableNames().size(), 0);
}

// Test case: Try to print a table
TEST(DatabaseTest, PrintTable) {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    db.createTable("users", columns);

    std::vector<std::string> row1 = {"1", "Alice"};
    std::vector<std::string> row2 = {"2", "Bob"};
    db.insertRow("users", row1);
    db.insertRow("users", row2);

    testing::internal::CaptureStdout();
    db.printTable("users");
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("id"), std::string::npos);
    EXPECT_NE(output.find("Alice"), std::string::npos);
    EXPECT_NE(output.find("Bob"), std::string::npos);
}