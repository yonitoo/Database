#include "Integer.h"
#include <cassert>

void Integer::copy(const Integer& other)
{
    this->setName(other.getName());
    this->str = other.str;
}

void Integer::erase()
{
    this->str.clear();
}

Integer::Integer() : ColumnType()
{
}

Integer::Integer(const std::string& name, const std::vector<std::string>& columnData) : ColumnType(name)
{
    for (unsigned int i = 0; i < columnData.size(); i++)
    {
        assert(columnData[i][0] == '+' || columnData[i][0] == '-' ||
            (columnData[i][0] >= '0' && columnData[i][0] <= '9'));
        this->str.push_back(columnData[i]);
    }
}
Integer& Integer::operator=(const Integer& other)
{
    if (this != &other)
    {
        erase();
        copy(other);
    }
    return *this;
}

Integer::~Integer()
{
    erase();
}

void Integer::setValueAt(const unsigned int index, const std::string& other)
{
    assert(index < this->str.size());
    assert(other[0] == '+' || other[0] == '-' ||
        (other[0] >= '0' && other[0] <= '9'));
    this->str[index] = other;
}

std::string Integer::getValueAt(const unsigned int index) const
{
    assert(index < this->str.size());
    return this->str[index];
}

unsigned int Integer::getSize() const
{
    return this->str.size();
}

void Integer::addElement(const std::string& str)
{
    if (str.size() == 0)
    {
        this->str.push_back("NULL");
        return;
    }
    std::cout << str << std::endl;
    assert(str[0] == '+' || str[0] == '-' ||
        (str[0] >= '0' && str[0] <= '9'));
    this->str.push_back(str);
}

std::string Integer::toString() const
{
    return "Integer";
}