#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <vector>
#include <map>    
#include <memory>

class Index {
    public:
        Index(const std::string& columnName, const std::vector<std::string>& columnValues);
        const std::string& getColumnName() const;

        // Add a value to the index
        void addValue(const std::string& value, size_t rowIndex);

        // Search for a value in the index
        std::vector<size_t> search(const std::string& value) const;        

    private:
        std::string columnName;                    // name of the column associated with the index
        std::map<std::string, std::vector<size_t>> indexData; // map of values to row indices in the table
};

#endif
