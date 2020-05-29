#ifndef TABLE_H
#define TABLE_H

#include "ColumnType.h"
#include <vector>

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

        void printColumnTypes() const;
        void printByPages(unsigned int) const;
        void print(std::ostream&) const;
        bool read(std::istream&);
};

#endif // TABLE_H
