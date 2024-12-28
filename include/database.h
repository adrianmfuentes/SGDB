#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <memory>
#include "table.h"

class Database {
    public:
        void createTable(const std::string& name, const std::vector<std::string>& columns);
        void insertRow(const std::string& tableName, const std::vector<std::string>& row);
        void printTable(const std::string& tableName) const;
        
        std::vector<std::string> getTableNames() const;
        Table& getTable(const std::string& tableName);

    private:
        void checkInvariants() const;  
        std::vector<std::unique_ptr<Table>> tables;
};

#endif
