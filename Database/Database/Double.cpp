#ifndef DOUBLE_CPP
#define DOUBLE_CPP

#include "Double.h"
#include <cassert>

void Double::copy(const Double& other)
{
    this->setName(other.getName());
    this->str = other.str;
}

void Double::erase()
{
    this->str.clear();
}

Double::Double() : ColumnType()
{
}

Double::Double(const std::string& name, const std::vector<std::string>& columnData) : ColumnType(name)
{
    for (unsigned int i = 0; i < columnData.size(); i++)
    {
        assert(columnData[i][0] == '+' || columnData[i][0] == '-' || 
           (columnData[i][0] >= '0' && columnData[i][0] <= '9'));
        this->str.push_back(columnData[i]);
    }
}
Double& Double::operator=(const Double& other)
{
    if (this != &other)
    {
        erase();
        copy(other);
    }
    return *this;
}

Double::~Double()
{
    erase();
}

void Double::setValueAt(const unsigned int index, const std::string& other)
{
    assert(index < this->str.size());
    assert(other[0] == '+' || other[0] == '-' ||
        (other[0] >= '0' && other[0] <= '9'));
    this->str[index] = other;
}

std::string Double::getValueAt(const unsigned int index) const
{
    assert(index < this->str.size());
    return this->str[index];
}

unsigned int Double::getSize() const
{
    return this->str.size();
}

void Double::addElement(const std::string& str)
{
    if (str.size() == 0)
    {
        this->str.push_back("NULL");
        return;
    }
    assert(str[0] == '+' || str[0] == '-' ||
        (str[0] >= '0' && str[0] <= '9'));
    this->str.push_back(str);
}

void Double::print(std::ostream& out) const
{
    if (!out)
    {
        return;
    }
    out << this->getName() << std::endl;

    for (unsigned int i = 0; i < this->str.size(); i++)
    {
        out << this->str[i] << std::endl;
    }
}

bool Double::read(std::istream& in)
{
    if (!in)
    {
        return false;
    }
    char sign;
    std::string strin;
    while (in.get() != '\t')
    {
        in >> sign;
        if (sign != '+' && sign != '-' && (sign < '0' || sign > '9'))
        {
            return false;
        }
        in >> strin;
        if (in)
        {
            this->str.push_back(sign + strin);
        }
        else
        {
            return false;
        }
    }
    return true;
}

std::string Double::toString() const
{
    return "Double";
}

#endif // DOUBLE_CPP
