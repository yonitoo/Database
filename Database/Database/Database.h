#ifndef DATABASE_H
#define DATABASE_H

#include "Table.h"
#include "Operation.h"

class Database
{
    private:
        std::vector<Table*> database;

        void copy(const Database&);

    public:
        Database();
        Database& operator=(const Database&);
        ~Database();

        void erase();

        Database& import(const std::string&);
        void showtables();
        void describe(const std::string&) const;
        void print(const std::string&) const;
        void exportt(const std::string&, const std::string&);

        std::vector<unsigned int> select(unsigned int, const std::string&, const std::string&);
        Table* addColumn(const std::string&, const std::string&, const ColumnType&);
        Table* update(const std::string&, unsigned int, const std::string&, unsigned int, const std::string&);
        Table* deletee(const std::string&, unsigned int, const std::string&);
        Table* insert(const std::string&, const std::vector<std::string>&);
        Table* innerjoin(const Table&, const std::vector<ColumnType*>&, Table, const std::vector<ColumnType*>&);

        void rename(const std::string&, const std::string&);
        unsigned int count(const std::string&, const unsigned int, const std::string&);
        double aggregate(const std::string&, unsigned int, const std::string&, unsigned int, const Operation&);

        void write(std::ostream&) const;
        bool read(std::istream&);
};

#endif // DATABASE_H
