#ifndef TABLE_H
#define TABLE_H

#include "ColumnType.h"

class Table
{
    private:
        std::string name;
        std::vector<ColumnType*> table;

        void copy(const Table&);
        void erase();

    public:
        Table();
        Table(const std::string&, const std::vector<ColumnType*>);
        Table(const Table&);
        Table& operator=(const Table&);
        ~Table();

        std::string getName() const;
        void setName(const std::string&);
        std::vector<std::vector<std::string>> getRows() const;
        void addColumn(const std::string&, const ColumnType&);
        void setValueAt(const unsigned int, const unsigned int, const std::string&);
        void removeRow(const unsigned int);
        void addRow(const std::vector<std::string>&);
        const std::vector<ColumnType*>& getTableData() const;
        void rowSwap(const unsigned int, const unsigned int);

        double findSum(const unsigned int, const std::vector<unsigned int>&) const;
        double findProduct(const unsigned int, const std::vector<unsigned int>&) const;
        double findMinimum(const unsigned int, const std::vector<unsigned int>&) const;
        double findMaximum(const unsigned int, const std::vector<unsigned int>&) const;

        void printColumnTypes() const;
        void printByPages(unsigned int) const;
        void print(std::ostream&) const;
        bool read(std::istream&);
};

#endif // TABLE_H
