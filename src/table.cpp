#include "table.h"
#include <iostream>
#include <set>

Table::Table(const std::string& name, const std::vector<std::string>& columns)
    : name(name), columns(columns) {
    checkInvariants(); 
}

void Table::insert(const std::vector<std::string>& row) {
    checkInvariants();

    if (row.size() != columns.size()) {
        std::cerr << "Error: Number of columns does not match the table structure!" << std::endl;
        return;
    }

    rows.push_back(row);

    for (const std::unique_ptr<Index>& index : indices) {
        const auto& columnName = index->getColumnName();
        size_t columnIndex = std::find(columns.begin(), columns.end(), columnName) - columns.begin();
        index->addValue(row[columnIndex], rows.size() - 1);  // Associate the new row with the index
    }

    checkInvariants();
}

void Table::createIndex(const std::string& columnName) {
    size_t columnIndex = std::find(columns.begin(), columns.end(), columnName) - columns.begin();

    if (columnIndex < columns.size()) {
        std::vector<std::string> columnValues;
        for (const auto& row : rows) { columnValues.push_back(row[columnIndex]); }
        indices.push_back(std::make_unique<Index>(columnName, columnValues));  // Create an index on the column

    } else { std::cerr << "Error: Column " << columnName << " not found!" << std::endl; }
}

std::vector<size_t> Table::searchIndex(const std::string& columnName, const std::string& value) const {
    for (const auto& index : indices) {
        if (index->getColumnName() == columnName) {
            return index->search(value);
        }
    }
    return {};  
}

const std::string& Table::getName() const {
    return name;  // Name of the table
}

size_t Table::getRowCount() const {
    return rows.size();  // Number of rows in the table
}

size_t Table::getColumnCount() const {
    return columns.size();  // Number of columns in the table
}

size_t Table::getIndexCount() const {
    return indices.size();  // Number of indices on the table
}

const std::vector<std::string>& Table::getRow(size_t rowIndex) const {
    if (rowIndex >= rows.size()) { throw std::out_of_range("Row index is out of range"); }
    return rows[rowIndex];  
}

const std::string& Table::getColumn(size_t columnIndex) const {
    if (columnIndex >= columns.size()) { throw std::out_of_range("Column index is out of range"); }
    return columns[columnIndex];  
}

const std::vector<std::string>& Table::getColumns() const {
    return columns;  // List of column names
}

const std::vector<std::vector<std::string>>& Table::getRows() const {
    return rows;  // List of rows
}

void Table::print() const {
    checkInvariants();

    std::cout << "Table: " << name << std::endl;
    for (const auto& column : columns) {
        std::cout << column << "\t";
    }
    std::cout << std::endl;

    for (const auto& row : rows) {
        for (const auto& cell : row) {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
    }
}

void Table::checkInvariants() const {
    if (columns.empty()) {
        std::cerr << "Error: Table " << name << " must have at least one column!" << std::endl;
        return;
    }

    for (const auto& column : columns) {
        if (column.empty()) {
            std::cerr << "Error: Table " << name << " has a column with an empty name!" << std::endl;
            return;
        }
    }

    std::set<std::string> columnSet(columns.begin(), columns.end());
    if (columnSet.size() != columns.size()) {
        std::cerr << "Error: Table " << name << " has duplicate columns!" << std::endl;
        return;
    }
}