#ifndef COLUMN_TYPE_H
#define COLUMN_TYPE_H

#include <iostream>
#include <string>

///TODO enum class Field = {Integer, Double, String}
class ColumnType
{
    private:
        std::string name;

    public:
        ColumnType();
        virtual ~ColumnType();
        virtual void print(std::ostream&) const = 0;
        virtual bool read(std::istream&) = 0;
};

#endif // COLUMN_TYPE_H
