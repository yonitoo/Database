#include <fstream>
#include <iterator>
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
        delete this->database[i];
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
    std::fstream file;
    file.open(fileName.c_str(), std::fstream::in);
    file.seekg(0, file.beg);
    if (file.is_open())
    {
        Table* table = new Table;
        table->read(file);
        for (unsigned int i = 0; i < this->database.size(); i++)
        {
            if (this->database[i]->getName() == table->getName() ||
                this->database[i]->getPath() == table->getPath())
            {
                std::cout << "Table with this name or path already exists" << std::endl;
                return *this;
            }
        }
        this->database.push_back(table);
    }
    file.close();
    std::string catalogueFile = "Catalogue.txt";
    file.open(catalogueFile.c_str(), std::fstream::out | std::fstream::trunc);
    if (file.is_open())
    {
        this->write(file);
    }
    return *this;
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

void Database::exportt(const std::string& tableName, const std::string& fileName)
{
    std::fstream file;
    file.open(fileName.c_str(), std::fstream::out | std::fstream::trunc);
    if (file.is_open())
    {
        for (unsigned int i = 0; i < this->database.size(); i++)
        {
            if (this->database[i]->getName() == tableName)
            {
                this->database[i]->write(file);
                return;
            }
        }
    }
    file.close();
}

std::vector<unsigned int> Database::select(unsigned int columnN, const std::string& value,
    const std::string& tableName)
{
    std::vector<unsigned int> indices;
    unsigned int tableIndex;
    for (unsigned int i = 0; i < this->database.size(); i++)
    {
        if (this->database[i]->getName() == tableName)
        {
            tableIndex = i;
            break;
        }
    }
    indices.push_back(tableIndex);

    for (unsigned int j = 0; j < this->database[tableIndex]->getRows().size(); j++)
    {
        if (this->database[tableIndex]->getRows()[j][columnN] == value)
        {
            indices.push_back(j);
        }
    }

    for (unsigned int i = 1; i < indices.size(); i++)
    {
        for (unsigned int j = 0; j < this->database[tableIndex]->getRows()[indices[i]].size(); j++)
        {
            std::cout << this->database[tableIndex]->getRows()[indices[i]][j];
            if (j < this->database[tableIndex]->getRows()[indices[i]].size() - 1)
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    return indices;
}

Table* Database::addColumn(const std::string& tableName, const std::string& columnName,
    const ColumnType& columnType)
{
    for (unsigned int i = 0; i < this->database.size(); i++)
    {
        if (this->database[i]->getName() == tableName)
        {
            this->database[i]->addColumn(columnName, columnType);
            return this->database[i];
        }
    }
    return nullptr;
}

Table* Database::update(const std::string& tableName, unsigned int columnSearch,
    const std::string& valueSearch, unsigned int columnTarget, const std::string& valueTarget)
{
    std::vector<unsigned int> indices = select(columnSearch, valueSearch, tableName);///vrushta mi indeksite
    for (unsigned int i = 1; i < indices.size(); i++)
    {
        this->database[indices[0]]->setValueAt(indices[i], columnTarget, valueTarget);
    }
    return this->database[indices[0]];
}

Table* Database::deletee(const std::string& tableName, unsigned int columnSearch,
    const std::string& valueSearch) ///trie redovete, sudurzhashti value v kolona columnSearch
{
    std::vector<unsigned int> indices = select(columnSearch, valueSearch, tableName);
    for (unsigned i = 1; i < indices.size(); i++)
    {
        this->database[indices[0]]->getRows().erase(this->database[indices[0]]->getRows().begin() + indices[i]);
    }
    return this->database[indices[0]];
}

Table* Database::insert(const std::string& tableName, const std::vector<std::string>& rowValues)
{
    for (unsigned int i = 0; i < this->database.size(); i++)
    {
        if (this->database[i]->getName() == tableName)
        {
            this->database[i]->addRow(rowValues);
            return this->database[i];
        }
    }
    return nullptr;
}

Table* Database::innerjoin(const Table& table1, const std::vector<ColumnType*>& table1Columns, 
                          Table table2, const std::vector<ColumnType*>& table2Columns)
{
    bool bool1 = false;
    bool bool2 = false;
    for (unsigned int i = 0; i < this->database.size(); i++)
    {
        if (this->database[i]->getName() == table1.getName())
        {
            bool1 = true;
        }
        if (this->database[i]->getName() == table2.getName())
        {
            bool1 = false;
        }
    }
    if (!bool1 || !bool2)
    {
        return nullptr;
    }

    std::vector<bool> isMutualFirst;
    std::vector<bool> isMutualSecond;
    unsigned int index1 = 0, index2 = 0;
    for (unsigned int i = 0; i < table1.getTableData()[0]->getSize(); i++)
    {
        isMutualFirst.push_back(false);
        isMutualSecond.push_back(false);
    }

    for (unsigned int i = 0; i < table1Columns.size(); i++)
    {
        for (unsigned int j = 0; j < table2Columns.size() ; j++)
        {
            if (table1Columns[i]->getName() == table2Columns[j]->getName()
                && table1Columns[i]->toString() == table2Columns[j]->toString())
            {
                isMutualFirst[i] = true;
                isMutualSecond[j] = true;
                index1 = i;
                index2 = j;
            }
        }
    }

    Table* newTable = new Table();
    for (unsigned int i = 0; i < table1Columns.size(); i++)
    {
        newTable->addColumn(table1Columns[i]->getName(), *table1Columns[i]);
    }

    for (unsigned int i = 0; i < table1Columns[index1]->getSize() ; i++)
    {
        for (unsigned int j = 0; j < table2Columns[index2]->getSize(); i++)
        {
            if (table1Columns[index1]->getValueAt(i) == table2Columns[index2]->getValueAt(j))
            {
                table2.rowSwap(i, j);
            }
        }
    }

    for (unsigned int i = 0; i < table2Columns.size() && isMutualSecond[i] == false ; i++)
    {
        newTable->addColumn(table2Columns[i]->getName(), *table2Columns[i]);
    }
    return newTable;
}

void Database::rename(const std::string& oldTableName, const std::string& newName)///greshka, ako ne e unikalno
{///vodi do promqna pri zapisvane posle vuv faila i v kataloga
    unsigned int tableIndex = 0;
    bool exists = true;
    for (unsigned int i = 0; i < this->database.size(); i++)
    {
        if (this->database[i]->getName() == oldTableName)
        {
            tableIndex = i;
            i++;
        }
        if (this->database[i]->getName() == newName)
        {
            exists = false;
        }
    }
    ///ideq za zarejdane na vsichki sushtestvuvashti tablici
    if (exists == true)
    {
        this->database[tableIndex]->setName(newName);
    }
    else
    {
        std::cout << "Table with name " << newName << " already exists!" << std::endl;
    }
}

unsigned int Database::count(const std::string& tableName, const unsigned int columnSearch,
    const std::string& valueSearch)
{
    return select(columnSearch, valueSearch, tableName).size() - 1;
}

double Database::aggregate(const std::string& tableName, unsigned int columnSearchIndex,
    const std::string& value, unsigned int targetColumn, const Operation& operation)
{
    std::vector<unsigned int> indices = select(columnSearchIndex, value, tableName);
    if (indices.size() == 1)
    {
        std::cout << "Nepravilni vhodni danni!" << std::endl;
        return 0.0;
    }

    if (this->database[indices[0]]->getTableData()[indices[1]]->toString() == "String")
    {
        std::cout << "Edna ili poveche koloni ne sa ot chislov tip ne e ot chislov tip!" << std::endl;
        return 0;
    }

    switch (operation)
    {
        case Operation::SUM: 
            return this->database[indices[0]]->findSum(targetColumn, indices);

        case Operation::PRODUCT : 
            return this->database[indices[0]]->findProduct(targetColumn, indices);

        case Operation::MINIMUM : 
            return this->database[indices[0]]->findMinimum(targetColumn, indices);

        case Operation::MAXIMUM : 
            return this->database[indices[0]]->findMaximum(targetColumn, indices);

        default: 
            std::cout << "Vuvedenata operaciq e nevalidna" << std::endl; 
            return 0.0;
    }
}

void Database::write(std::ostream& out) const
{
    for (unsigned int i = 0; i < this->database.size(); i++)
    {
        out << this->database[i]->getName() << '|' << this->database[i]->getPath() << '|' << std::endl;
    }
}

bool Database::read(std::istream& in)
{
    if (!in)
    {
        return false;
    }
    std::string line;
    std::fstream tableFile;
    unsigned int index = 0;
    std::string name;
    while (std::getline(in, line, '|'))
    {
        if (index % 2 == 0)
        {
            name = line;
        }
        if (index % 2 == 1)
        {
            Table* table = new Table;
            table->setName(name);
            table->setPath(line);
            tableFile.open(line, std::fstream::in);
            tableFile.seekg(0, tableFile.beg);
            table->read(tableFile);
            tableFile.close();
            this->database.push_back(table);
        }
        index++;
        if (index % 2 == 0)
        {
            in.get();
        }
    }
    if (!in)
    {
        return false;
    }
    return true;
}