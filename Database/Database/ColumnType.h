#ifndef COLUMN_TYPE_H
#define COLUMN_TYPE_H

#include <iostream>
#include <string>
#include <vector>


///TODO da dobavq NULL stojnosti
class ColumnType
{
    protected:
        std::string name;
        std::vector<std::string> str;

    public:
        ColumnType();
        ColumnType(const std::string&);
        virtual ~ColumnType();

        void setName(const std::string&);
        std::string getName() const;
        virtual void setValueAt(const unsigned int, const std::string&) = 0;
        virtual std::string getValueAt(const unsigned int) const = 0;
        virtual unsigned int getSize() const = 0;
        virtual const std::vector<std::string>& getVector() const;
        virtual void addElement(const std::string&) = 0;
        virtual std::string toString() const = 0;
};

#endif // COLUMN_TYPE_H
