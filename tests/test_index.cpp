#include <gtest/gtest.h>
#include "index.h"
#include "database.h"

// Test case: Create a valid index
TEST(IndexTest, CreateIndex) {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    db.createTable("users", columns);

    std::vector<std::string> row1 = {"1", "Alice"};
    std::vector<std::string> row2 = {"2", "Bob"};
    db.insertRow("users", row1);
    db.insertRow("users", row2);

    db.getTable("users").createIndex("name");
    EXPECT_EQ(db.getTable("users").getIndexCount(), 1);
}

// Test case: Try to search in a valid index
TEST(IndexTest, SearchIndexValid) {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    db.createTable("users", columns);

    std::vector<std::string> row1 = {"1", "Alice"};
    std::vector<std::string> row2 = {"2", "Bob"};
    db.insertRow("users", row1);
    db.insertRow("users", row2);

    db.getTable("users").createIndex("name");
    auto result = db.getTable("users").searchIndex("name", "Alice");

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 0);
}

// Test case: Try to search in an index that does not exist
TEST(IndexTest, SearchIndexNonExistent) {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    db.createTable("users", columns);

    std::vector<std::string> row1 = {"1", "Alice"};
    std::vector<std::string> row2 = {"2", "Bob"};
    db.insertRow("users", row1);
    db.insertRow("users", row2);

    db.getTable("users").createIndex("name");
    auto result = db.getTable("users").searchIndex("name", "Charlie");

    EXPECT_EQ(result.size(), 0);  
}