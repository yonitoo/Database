#ifndef DATABASE_H
#define DATABASE_H

#include "Table.h"

class Database
{
    private:
        std::vector<Table*> database;

        void copy(const Database&);
        void erase();

    public:
        Database();
        Database& operator=(const Database&);
        ~Database();

        Database& import(const std::string&);///char* file name + dobavq se v kataloga
        void showtables();
        void describe(const std::string&) const;///info za tipovete na kolonite na tablica s char* ime
        void print(const std::string&) const;///redovete na tablica po stranici(dialog - sledv,pred, izhod)
        void export(const std::string& tableName, const std::string& fileName);///zapisva q vuv file
        void select(unsigned int, const std::string& value,
                    const std::string& tableName);///printva vs redove, chiito koloni imat value
        Table& addColumn(const std::string& tableName, columnName(?),
                         Field& columnType);///v kraq s NULL st/sti
        Table& update(const std::string& tableName, unsigned int columnSearch,
                      Field& valueSearch, unsigned int columnTarget, Field& valueTarget);
        Table& deletee(const std::string& tableName, unsigned int columnSearch,
                      Field& valueSearch); ///trie redovete, sudurzhashti value v kolona columnSearch
        Table& insert(const std::string& tableName, Field& rowValue1, Field& ...,
                      Field& rowValueN); ///nov red
        Table innerjoin(Table&, unsigned int table1Column, Table&, unsigned int table2Column);
        Table& rename(const std::string& oldTableName, const std::string& newName);///greshka, ako ne e unikalno
        unsigned int count(const std::string& TableName, unsigned int columnSearch,
                            Field& valueSearch); ///broq na rows, za koito columnSearch sudurja value
        unsigned int aggregate(const std::string& tableName, unsigned int columnSearchIndex,
                     Field& value, unsigned int targetColumn, Operation);
                     ///operacii : sum, product, min, max
};

#endif // DATABASE_H
