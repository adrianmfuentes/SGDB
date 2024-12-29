#include "../include/index.h"
#include <iostream>

Index::Index(const std::string& columnName, const std::vector<std::string>& columnValues)
    : columnName(columnName) {
    // Initialize the index with the column values
    for (size_t i = 0; i < columnValues.size(); ++i) {
        addValue(columnValues[i], i);  
    }
}

void Index::addValue(const std::string& value, size_t rowIndex) {
    indexData[value].push_back(rowIndex);
}

std::vector<size_t> Index::search(const std::string& value) const {
    auto it = indexData.find(value);
    if (it != indexData.end()) {
        return it->second;  
    } 

    return {};  // If the value is not found, return an empty vector
}

const std::string& Index::getColumnName() const {
    return columnName;  // Return the name of the column associated with the index
}
