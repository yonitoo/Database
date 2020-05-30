#include "Table.h"
#include "Integer.h"
#include "Double.h"
#include "String.h"
#include <iterator>
#include <cassert>
#include <algorithm>

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

    this->path = other.path;
}

void Table::erase()
{
    for(unsigned int i = 0 ;  i < this->table.size() ; i++)
    {
        this->table[i]->~ColumnType();
    }
    this->table.clear();
}

Table::Table() : name(""),table(), path("")
{
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

std::vector<std::vector<std::string>> Table::getRows() const
{
    std::vector<std::vector<std::string>> rows;
    for (unsigned int i = 0; i < this->table[0]->getSize(); i++)
    {
        rows.push_back(std::vector<std::string>());
    }
    for (unsigned int i = 0; i < this->table[0]->getSize(); i++)
    {
        for (unsigned int j = 0; j < this->table.size(); j++)
        {
            rows[i].push_back(this->table[j]->getValueAt(i));
        }
    }
    return rows;
}

const std::string& Table::getPath() const
{
    return this->path;
}

void Table::setPath(const std::string& path)
{
    this->path = path;
}

void Table::addColumn(const std::string& columnName, const ColumnType& columnType)
{
    if (columnType.toString() == "Integer")
    {
        this->table.push_back(new Integer);
    }
    else if (columnType.toString() == "Double")
    {
        this->table.push_back(new Double);
    }
    else if (columnType.toString() == "String")
    {
        this->table.push_back(new String);
    }
    for (unsigned int i = 0; i < columnType.getVector().size(); i++)
    {
        this->table[this->table.size() - 1]->addElement(columnType.getVector()[i]);
    }
    this->table[this->table.size() - 1]->setName(columnName);
}

void Table::setValueAt(const unsigned int row, const unsigned int col, const std::string& value)
{
    this->table[col]->setValueAt(row, value);
}

void Table::removeRow(const unsigned int index)
{
    assert(index < this->getRows().size());
    //TODO da fixna
    this->getRows().erase(this->getRows().begin() + index);
}

void Table::addRow(const std::vector<std::string>& rowData)
{
    for (unsigned int i = 0; i < table.size(); i++)
    {
        if (i < rowData.size())
        {
            this->table[i]->addElement(rowData[i]);
        }
        else
        {
            this->table[i]->addElement("");
        }
    }
}

const std::vector<ColumnType*>& Table::getTableData() const
{
    return this->table;
}

void Table::rowSwap(const unsigned int index1, const unsigned int index2)
{
    std::string temp;
    for (unsigned int i = 0; i < this->table.size(); i++)
    {
        temp = this->table[i]->getValueAt(index1);
        this->table[i]->setValueAt(index1, this->table[i]->getValueAt(index2));
        this->table[i]->setValueAt(index2, temp);
    }
}

double Table::findSum(const unsigned int targetColumn, const std::vector<unsigned int>& indices) const
{
    double sum = 0;

    for (unsigned int i = 1; i < indices.size(); i++)
    {
        if (this->table[indices[i]]->toString() == "String")
        {
            std::cout << "Edna ili poveche koloni ne sa ot chislov tip!" << std::endl;
            return 0.0;
        }

        sum = sum + std::stod(this->table[indices[i]]->getValueAt(targetColumn));
    }

    return sum;
}

double Table::findProduct(const unsigned int targetColumn, const std::vector<unsigned int>& indices) const
{
    double product = 1;

    for (unsigned int i = 1; i < indices.size(); i++)
    {
        if (this->table[indices[i]]->toString() == "String")
        {
            std::cout << "Edna ili poveche koloni ne sa ot chislov tip!" << std::endl;
            return 0.0;
        }
        product = product*std::stod(this->table[indices[i]]->getValueAt(targetColumn));
    }
    return product;
}

double Table::findMinimum(const unsigned int targetColumn, const std::vector<unsigned int>& indices) const
{
    double eps = 2e-52, min = std::stod(this->table[indices[1]]->getValueAt(targetColumn));

    for (unsigned int i = 2; i < indices.size(); i++)
    {
        if (this->table[indices[i]]->toString() == "String")
        {
            std::cout << "Edna ili poveche koloni ne sa ot chislov tip!" << std::endl;
            return 0.0;
        }

        if (min - std::stod(this->table[indices[i]]->getValueAt(targetColumn)) > eps)
        {
            min = std::stod(this->table[indices[i]]->getValueAt(targetColumn));
        }
    }

    return min;
}

double Table::findMaximum(const unsigned int targetColumn, const std::vector<unsigned int>& indices) const
{
    double eps = 2e-52, max = std::stod(this->table[indices[1]]->getValueAt(targetColumn));

    for (unsigned int i = 2; i < indices.size(); i++)
    {
        if (this->table[indices[i]]->toString() == "String")
        {
            std::cout << "Edna ili poveche koloni ne sa ot chislov tip!" << std::endl;
            return 0.0;
        }

        if (std::stod(this->table[indices[i]]->getValueAt(targetColumn)) - max > eps)
        {
            max = std::stod(this->table[indices[i]]->getValueAt(targetColumn));
        }
    }

    return max;
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

void Table::write(std::ostream& out) const
{
    for (unsigned int i = 0; i < this->table.size(); i++)
    {
        out << this->table[i]->getName() << "|" << this->table[i]->toString();
        if (i != this->table.size() - 1)
        {
            out << '|';
        }
    }
    out << std::endl;

    for (unsigned int i = 0; i < this->table[0]->getSize(); i++)
    {
        for (unsigned int j = 0; j < this->table.size(); j++)
        {
            out << this->table[j]->getValueAt(i);
            if (j != this->table.size() - 1)
            {
                out << '|';
            }
        }
        out << std::endl;
    }
}

bool Table::read(std::istream& in)
{
    if (!in)
    {
        return false;
    }
    std::string name;
    std::string columnType;
    std::string line;
    std::vector<ColumnType*> table;
    unsigned int index = 0;
    char currentCharacter = '\0';
    std::string currentString;
    while (currentCharacter != '\n' && currentCharacter != '\r\n' && currentCharacter != '\r')
    {
        currentCharacter = in.get();
        name = "";
        columnType = "";
        while (currentCharacter != '|')
        {
            if (index % 2 == 0)
            {
                name += currentCharacter;
            }
            else
            {
                columnType += currentCharacter;
            }
            currentCharacter = in.get();
            if (currentCharacter == '\n' || currentCharacter == '\r\n' || currentCharacter == '\r')
            {
                break;
            }
        }
        if (index % 2 == 1)
        {
            if (columnType == "Integer")
            {
                Integer* column = new Integer;
                column->setName(name);
                table.push_back(column);
            }
            else if (columnType == "Double")
            {
                Double* column = new Double;
                column->setName(name);
                table.push_back(column);
            }
            else
            {
                String* column = new String;
                column->setName(name);
                table.push_back(column);
            }
        }
        index++;
    }
    if (!in)
    {
        return false;
    }

    index = 0;
    while (std::getline(in, line, '|'))
    {
        ///razmestvane, da se OPRAVI!!!
        std::cout << table[index % table.size()]->toString() << std::endl;
        std::cout << line << std::endl;
        table[index % table.size()]->addElement(line);
        index++;
    }
    this->table = table;
    return true;
}