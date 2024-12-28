#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include "index.h"

class Table {
    public:
        Table(const std::string& name, const std::vector<std::string>& columns);
        void insert(const std::vector<std::string>& row);

        void createIndex(const std::string& columnName);
        std::vector<size_t> searchIndex(const std::string& columnName, const std::string& value) const;
        
        size_t getRowCount() const;
        size_t getColumnCount() const;
        size_t getIndexCount() const;

        void print() const;
        const std::string& getName() const;

        const std::string& getColumn(size_t columnIndex) const;
        const std::vector<std::string>& getRow(size_t rowIndex) const;

        const std::vector<std::string>& getColumns() const;
        const std::vector<std::vector<std::string>>& getRows() const;

    private:
        std::string name;
        std::vector<std::string> columns;
        std::vector<std::vector<std::string>> rows;
        void checkInvariants() const;
        std::vector<std::unique_ptr<Index>> indices;  // List of indices on this table
};

#endif
