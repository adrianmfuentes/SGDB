#include "../include/database.h"
#include <iostream>
#include <set>
#include <memory>  // For std::make_unique


void Database::createTable(const std::string& name, const std::vector<std::string>& columns) {
    checkInvariants();
    tables.push_back(std::make_unique<Table>(name, columns));
}

void Database::insertRow(const std::string& tableName, const std::vector<std::string>& row) {
    checkInvariants();

    for (const auto& table : tables) {
        if (table->getName() == tableName) {

            if (row.size() != table->getColumns().size()) {
                std::cerr << "Error: Row does not match the number of columns!" << std::endl;
                return;  // Abort if the row size does not match the number of columns
            }
            
            table->insert(row);  
            checkInvariants();
            return;
        }
    }

    std::cerr << "Error: Table " << tableName << " not found!" << std::endl;
}

std::vector<std::string> Database::getTableNames() const {
    std::vector<std::string> tableNames;
    for (const auto& table : tables) { 
        tableNames.push_back(table->getName());  
    }
    return tableNames;
}

Table& Database::getTable(const std::string& tableName) {
    for (const auto& table : tables) {
        if (table->getName() == tableName) {
            return *table;
        }
    }

    throw std::runtime_error("Table not found: " + tableName);
}

void Database::printTable(const std::string& tableName) const {
    checkInvariants();

    for (const auto& table : tables) {
        if (table->getName() == tableName) {
            table->print();
            return;
        }
    }
    std::cerr << "Error: Table " << tableName << " not found!" << std::endl;
}

void Database::checkInvariants() const {
    // Check that no table has a duplicate name
    std::set<std::string> tableNames;
    for (const auto& table : tables) {
        if (tableNames.find(table->getName()) != tableNames.end()) {
            std::cerr << "Error: Duplicate table name: " << table->getName() << std::endl;
            return;
        }
        tableNames.insert(table->getName());
    }

    // Check every table meets the invariants
    for (const auto& table : tables) {
        // Check that the table has at least one column
        if (table->getColumns().empty()) {
            std::cerr << "Error: Table " << table->getName() << " must have at least one column!" << std::endl;
            return;
        }

        // Check that no column has a duplicate name
        std::set<std::string> columnNames(table->getColumns().begin(), table->getColumns().end());
        if (columnNames.size() != table->getColumns().size()) {
            std::cerr << "Error: Table " << table->getName() << " has duplicate columns!" << std::endl;
            return;
        }

        // Check that no column has an empty name
        for (const auto& column : table->getColumns()) {
            if (column.empty()) {
                std::cerr << "Error: Table " << table->getName() << " has a column with an empty name!" << std::endl;
                return;
            }
        }
    }
}
