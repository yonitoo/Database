#ifndef DATABASE_CPP
#define DATABASE_CPP

#include <fstream>
#include "Database.h"

void Database::copy(const Database& other)
{
    for(unsigned int i = 0 ; i < other.database.size() ; i++)
    {
        this->database.push_back(other.database[i]);
    }
}

void Database::erase()
{
    for(unsigned int i = 0 ; i < this->database.size() ; i++)
    {
        this->database[i]->~Table();
    }
    this->database.clear();
}

Database::Database() : database()
{

}
Database& Database::operator=(const Database& other)
{
    if(this != &other)
    {
        erase();
        copy(other);
    }
    return *this;
}

Database::~Database()
{
    erase();
}

Database& Database::import(const std::string& fileName)///char* file name + dobavq se v kataloga
{

}

void Database::showtables()
{
    for(unsigned int i = 0 ; i < this->database.size() ; i++)
    {
        std::cout << this->database[i]->getName() << std::endl;
    }
}

void Database::describe(const std::string& tableName) const
{
    for(unsigned int i = 0 ; i < this->database.size() ; i++)
    {
        if(this->database[i]->getName() == tableName)
        {
            this->database[i]->printColumnTypes();
        }
    }
}
void Database::print(const std::string& tableName) const
{
    for (unsigned int i = 0; i < this->database.size(); i++)
    {
        if (this->database[i]->getName() == tableName)
        {
            this->database[i]->printByPages(0);
            return;
        }
    }
}

void Database::export(const std::string& tableName, const std::string& fileName)///zapisva q vuv file
{
    std::fstream file;
    file.open(fileName.c_str(), std::fstream::out | std::fstream::trunc);
    if (file.is_open())
    {
        for (unsigned int i = 0; i < this->database.size(); i++)
        {
            if (this->database[i]->getName() == tableName)
            {
                this->database[i]->print(file);
                return;
            }
        }
    }
    file.close();
}

void Database::select(unsigned int columnN, const std::string& value,
    const std::string& tableName)///printva vs redove, chiito koloni imat value
{
    for (unsigned int i = 0; i < this->database.size(); i++)
    {
        if (this->database[i]->getName() == tableName)
        {
            for (unsigned int j = 0; j < this->database[i]->getRows() ; j++)
            {
                if ()
                {
                    this->database[i]->getRows()[j].print();
                }
            }
                this->database[i]->
            return;
        }
    }
}

Table& Database::addColumn(const std::string& tableName, const std::string& columnName,
    const std::string& columnType)
{
    for (unsigned int i = 0; i < this->database.size(); i++)
    {
        if (this->database[i]->getName() == tableName)
        {
            this->database[i]->
        }
    }
}

Table& Database::update(const std::string& tableName, unsigned int columnSearch,
    Field& valueSearch, unsigned int columnTarget, Field& valueTarget)
{
    select(columnSearch, valueSearch, tableName);
    ///smenqm na select column
    ///select da vrushta redovete, koito e nameril(index ili stojnosti)
}

Table& Database::deletee(const std::string& tableName, unsigned int columnSearch,
    Field& valueSearch) ///trie redovete, sudurzhashti value v kolona columnSearch
{

}

Table& Database::insert(const std::string& tableName, Field& rowValue1, Field& ...,
    Field& rowValueN) ///nov red
{

}

Table Database::innerjoin(Table&, unsigned int table1Column, Table&, unsigned int table2Column)
{

}

Table& Database::rename(const std::string& oldTableName, const std::string& newName)///greshka, ako ne e unikalno
{

}

unsigned int Database::count(const std::string& TableName, unsigned int columnSearch,
    Field& valueSearch) ///broq na rows, za koito columnSearch sudurja value]
{
    ///kolko reda vrushta select
}

unsigned int Database::aggregate(const std::string& tableName, unsigned int columnSearchIndex,
    Field& value, unsigned int targetColumn, Operation)
{

}

#endif // DATABASE_CPP