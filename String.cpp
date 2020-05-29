#ifndef STRING_CPP
#define STRING_CPP

#include "String.h"
#include <string>
#include <cassert>

void String::copy(const String& other)
{
    this->setName(other.getName());
    for (unsigned int i = 0; i < other.str.size(); i++)
    {
        this->str.push_back(other.str[i]);
    }
}

void String::erase()
{
    str.clear();
}

String::String() : ColumnType()
{
}

String::String(const std::string& name, const std::vector<std::string>& otherStr)
{
    this->setName(name);
    for (unsigned int i = 0; i < otherStr.size(); i++)
    {
        this->str.push_back(otherStr[i]);
    }
}

String& String::operator=(const String& other)
{
    if (this != &other)
    {
        erase();
        copy(other);
    }
    return *this;
}

String::~String()
{
    erase();
}

void String::setValueAt(const unsigned int index, const std::string& otherStr)
{
    assert(index < this->str.size());
    this->str[index] = otherStr;
}

std::string String::getValueAt(const unsigned int index) const
{
    if (index >= this->str.size())
    {
        return "";
    }
    else
    {
        return this->str[index];
    }
}

unsigned int String::getSize() const
{
    return this->str.size();
}

void String::addElement(const std::string& str)
{
    if (str.size() == 0)
    {
        this->str.push_back("NULL");
        return;
    }
    this->str.push_back(str);
}

void String::print(std::ostream& out) const
{
    if(!out)
    {
        return;
    }
    out << this->getName() << std::endl;
    for (unsigned int i = 0; i < this->str.size(); i++)
    {
        out << '"' << this->str[i] << '"' << std::endl;
    }
}

bool String::read(std::istream& in)
{
    if (!in)
    {
        return false;
    }
    
    std::string currentStr;
    while (in.get() != '\t')
    {
        in >> currentStr;
        if (currentStr[0] != '"' || currentStr[currentStr.size() - 1] != '"')
        {
            return false;
        }

        if (in)
        {
            this->str.push_back(currentStr);
        }
        else
        {
            return false;
        }
    }
    return true;
}

std::string String::toString() const
{
	return "String";
}

#endif
