#include "Table.h"
#include "Integer.h"
#include "Double.h"
#include "String.h"

void Table::copy(const Table& other)
{
    this->name = other.name;
    for (unsigned int i = 0; i < other.table.size(); i++)
    {
        if (other.table[i]->toString() == "String")
        {
            this->table.push_back(new String);
        }
        else if (other.table[i]->toString() == "Double")
        {
            this->table.push_back(new Double);
        }
        else if (other.table[i]->toString() == "Integer")
        {
            this->table.push_back(new Integer);
        }
    }

    for(unsigned int i = 0 ; i < this-> table.size(); i++)
    {
        for(unsigned int j = 0 ; j < other.table[i]->getSize() ; j++)
        {
            this->table[i]->addElement(other.table[i]->getValueAt(j));
        }
    }
}

void Table::erase()
{
    for(unsigned int i = 0 ;  i < this->table.size() ; i++)
    {
        this->table[i]->~ColumnType();
    }
    this->table.clear();
}

Table::Table() : name(""),table()
{
}

Table::Table(const std::string& name, const std::vector<ColumnType*> table)
{
    this->name = name;
    for(unsigned int i = 0 ; i < table.size() ; i++)
    {
        if (table[i]->toString() == "Integer")
        {
            this->table.push_back(new Integer);
        }
        else if (table[i]->toString() == "Double")
        {
            this->table.push_back(new Double);
        }
        else if (table[i]->toString() == "String")
        {
            this->table.push_back(new String);
        }
    }

    for(unsigned int i = 0 ; i < this->table.size() ; i++)
    {
        for(unsigned int j = 0 ; j < this->table[i]->getSize() ; j++)
        {
            this->table[i]->addElement(table[i]->getValueAt(j));
        }
    }
}

Table::Table(const Table& other)
{
    copy(other);
}

Table& Table::operator=(const Table& other)
{
    if(this != &other)
    {
        erase();
        copy(other);
    }
    return *this;
}
Table::~Table()
{
    erase();
}

std::string Table::getName() const
{
    return this->name;
}

void Table::setName(const std::string& name)
{
    this->name = name;
}

void Table::printColumnTypes() const
{
    for(unsigned int i = 0 ; i < this->table.size() ; i++)
    {
        std::cout << this->table[i]->toString();
        if (i != this->table.size() - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void Table::printByPages(unsigned int counter) const
{
    std::string command;
    unsigned int rowSize = this->table[0]->getSize();
    while (true)
    {
        std::getline(std::cin, command);
        if (command != "Next" && command != "Previous")
        {
            break;
        }
        if (command == "Next")
        {
            counter += 10;
        }
        else
        {
            counter -= 10;
        }

        for (unsigned int i = counter; i < counter + 10 && i < rowSize; i++)
        {
            for (unsigned int j = 0; j < this->table.size(); j++)
            {
                std::cout << this->table[j]->getValueAt(i);
                if (j != this->table.size() - 1)
                {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}

void Table::print(std::ostream& out) const
{
    if(!out)
    {
        return;
    }
    out << this->name << std::endl;
    for(unsigned int i = 0 ; i < this->table[0]->getSize() ; i++)
    {
        for(unsigned int j = 0 ; j < this->table.size() ; j++)
        {
            std::cout << this->table[j]->getValueAt(i);
            if (j != this->table.size() - 1)
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool Table::read(std::istream& in)
{
    if(!in)
    {
        return false;
    }
    std::string name;
    std::string line;
    std::vector<std::string> table;
    std::getline(in, name);
    unsigned int index = 0;
    while (std::getline(in, line, ' '))
    {
        in >> table[index]
    }
    /*std::string name;
    in >> name;
    std::vector<ColumnType*> table;
    for(unsigned int i = 0 ; i < this->table.size() ; i++)
    {
        table[i]->read(in);
    }
    in.get();

    if(in)
    {
        this->setName(name);
        for(unsigned int i = 0 ; i < table[0].size() ; i++)
        {
            for(unsigned int j = 0 ; j < this->table[i]->getSize() ; j++)
            {
                this->table[i]->addElement(j) =
            }
        }
        return true;
    }
    else
    {
        if(in.eof())
        {
            std::cout << "The end of file has been reached!" << std::endl;
        }
        else
        {
            in.clear();
            in.ignore(1024, '\n');
        }
        return false;
    }*/
}