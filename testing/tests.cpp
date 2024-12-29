#include <iostream>       // For std::cout, std::cerr
#include <vector>         // For std::vector
#include <string>         // For std::string
#include <sstream>        // For std::ostringstream
#include <cassert>        // For assert

#include "../include/database.h"  
#include "../include/table.h"     

void testCreateTableInDatabase() {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    
    db.createTable("users", columns);
    
    auto tableNames = db.getTableNames();
    assert(tableNames.size() == 1);  
    assert(tableNames[0] == "users");  
    
    std::cout << "testCreateTableInDatabase passed!" << std::endl;
}

void testCreateTableWithEmptyColumns() {
    Database db;
    std::vector<std::string> columns = {};  

    std::streambuf* old_cerr_buf = std::cerr.rdbuf();
    std::ostringstream oss;
    std::cerr.rdbuf(oss.rdbuf());

    db.createTable("users", columns);
    std::cerr.rdbuf(old_cerr_buf);

    std::string output = oss.str();
    assert(output.find("Error: Table users must have at least one column!") != std::string::npos);

    std::cout << "testCreateTableWithEmptyColumns passed!" << std::endl;
}

void testCreateTableWithDuplicateColumns() {
    Database db;
    std::vector<std::string> columns = {"id", "name", "id"};  

    std::streambuf* old_cerr_buf = std::cerr.rdbuf();
    std::ostringstream oss;
    std::cerr.rdbuf(oss.rdbuf());

    db.createTable("users", columns);
    std::cerr.rdbuf(old_cerr_buf);

    std::string output = oss.str();
    assert(output.find("Error: Table users has duplicate columns!") != std::string::npos);

    std::cout << "testCreateTableWithDuplicateColumns passed!" << std::endl;
}

void testInsertRowInDatabase() {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    
    db.createTable("users", columns);  
    std::vector<std::string> row = {"1", "Alice"};
    db.insertRow("users", row); 
    
    auto& table = db.getTable("users");
    assert(table.getRowCount() == 1); 
    assert(table.getRow(0)[0] == "1");  
    assert(table.getRow(0)[1] == "Alice");  
    
    std::cout << "testInsertRowInDatabase passed!" << std::endl;
}

void testInsertInvalidRow() {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    
    db.createTable("users", columns);  
    std::vector<std::string> row = {"1"};  
    db.insertRow("users", row);
    
    auto& table = db.getTable("users");
    assert(table.getRowCount() == 0); 

    std::cout << "testInsertInvalidRow passed!" << std::endl;
}

void testInsertRowInNonexistentTable() {
    Database db;
    std::vector<std::string> row = {"1", "Alice"};
    
    std::streambuf* old_cerr_buf = std::cerr.rdbuf();
    std::ostringstream oss;
    std::cerr.rdbuf(oss.rdbuf());

    db.insertRow("nonexistent_table", row);
    std::cerr.rdbuf(old_cerr_buf);

    std::string output = oss.str();
    assert(output.find("Error: Table nonexistent_table not found!") != std::string::npos);

    std::cout << "testInsertRowInNonexistentTable passed!" << std::endl;
}

void testGetTable() {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    
    db.createTable("users", columns);  
    
    auto& table = db.getTable("users");
    assert(table.getName() == "users"); 
    
    std::cout << "testGetTable passed!" << std::endl;
}

void testCreateIndex() {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    db.createTable("users", columns);

    std::vector<std::string> row1 = {"1", "Alice"};
    std::vector<std::string> row2 = {"2", "Bob"};
    db.getTable("users").insert(row1);
    db.getTable("users").insert(row2);
    db.getTable("users").createIndex("name");

    assert(db.getTable("users").getIndexCount() == 1);

    std::cout << "testCreateIndex passed!" << std::endl;
}

void testSearchIndexValid() {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    db.createTable("users", columns);

    std::vector<std::string> row1 = {"1", "Alice"};
    std::vector<std::string> row2 = {"2", "Bob"};
    db.getTable("users").insert(row1);
    db.getTable("users").insert(row2);

    db.getTable("users").createIndex("name");
    auto result = db.getTable("users").searchIndex("name", "Alice");

    assert(result.size() == 1);
    assert(result[0] == 0);  
    
    std::cout << "testSearchIndexValid passed!" << std::endl;
}

void testSearchIndexNonExistent() {
    Database db;
    std::vector<std::string> columns = {"id", "name"};
    db.createTable("users", columns);

    std::vector<std::string> row1 = {"1", "Alice"};
    std::vector<std::string> row2 = {"2", "Bob"};
    db.getTable("users").insert(row1);
    db.getTable("users").insert(row2);

    db.getTable("users").createIndex("name");
    auto result = db.getTable("users").searchIndex("name", "Charlie");
    assert(result.size() == 0);
    
    std::cout << "testSearchIndexNonExistent passed!" << std::endl;
}

void testCreateValidTable() {
    std::vector<std::string> columns = {"id", "name"};
    Table table("users", columns);

    assert(table.getName() == "users");
    assert(table.getColumnCount() == 2);
    assert(table.getColumn(0) == "id");
    assert(table.getColumn(1) == "name");

    std::cout << "testCreateValidTable passed!" << std::endl;
}

void testInsertValidRow() {
    std::vector<std::string> columns = {"id", "name"};
    Table table("users", columns);

    std::vector<std::string> row = {"1", "Alice"};
    table.insert(row);

    assert(table.getRowCount() == 1);
    assert(table.getRow(0)[0] == "1");
    assert(table.getRow(0)[1] == "Alice");

    std::cout << "testInsertValidRow passed!" << std::endl;
}

void testInsertRowWithWrongColumnCount() {
    std::vector<std::string> columns = {"id", "name"};
    Table table("users", columns);

    std::vector<std::string> row = {"1"};  
    table.insert(row);

    assert(table.getRowCount() == 0);

    std::cout << "testInsertRowWithWrongColumnCount passed!" << std::endl;
}

void testInsertEmptyRow() {
    std::vector<std::string> columns = {"id", "name"};
    Table table("users", columns);

    std::vector<std::string> row = {};  
    table.insert(row);

    assert(table.getRowCount() == 0);

    std::cout << "testInsertEmptyRow passed!" << std::endl;
}

void testInsertRowWithEmptyColumn() {
    std::vector<std::string> columns = {"id", "name"};
    Table table("users", columns);

    std::vector<std::string> row = {"1", ""};  
    table.insert(row);

    assert(table.getRowCount() == 1);
    assert(table.getRow(0)[1] == "");  

    std::cout << "testInsertRowWithEmptyColumn passed!" << std::endl;
}

void testPrintTable() {
    std::vector<std::string> columns = {"id", "name"};
    Table table("users", columns);

    std::vector<std::string> row1 = {"1", "Alice"};
    std::vector<std::string> row2 = {"2", "Bob"};
    table.insert(row1);
    table.insert(row2);

    std::streambuf* old_buf = std::cout.rdbuf(); 
    std::ostringstream oss;  
    std::cout.rdbuf(oss.rdbuf());  

    table.print();
    
    std::string output = oss.str();
    assert(output.find("id") != std::string::npos);
    assert(output.find("Alice") != std::string::npos);
    assert(output.find("Bob") != std::string::npos);

    std::cout.rdbuf(old_buf); 

    std::cout << "testPrintTable passed!" << std::endl;
}

int main() {
    testCreateTableInDatabase();
    testCreateTableWithEmptyColumns();
    testCreateTableWithDuplicateColumns();
    testInsertRowInDatabase();
    testInsertInvalidRow();
    testInsertRowInNonexistentTable();
    testCreateIndex();
    testSearchIndexValid();
    testSearchIndexNonExistent();
    testCreateValidTable();
    testInsertValidRow();
    testInsertRowWithWrongColumnCount();
    testInsertEmptyRow();
    testInsertRowWithEmptyColumn();
    testPrintTable();

    // Print a beautiful message if all tests pass
    std::cout << "\n All tests passed successfully!" << std::endl;
    return 0;
}
