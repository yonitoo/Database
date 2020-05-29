#include "ColumnType.h"

ColumnType::ColumnType() : name(""), str()
{
}

ColumnType::ColumnType(const std::string& name) : name(name), str()
{
}

ColumnType::~ColumnType()
{
	str.clear();
}

void ColumnType::setName(const std::string& name)
{
	this->name = name;
}

std::string ColumnType::getName() const
{
	return this->name;
}

const std::vector<std::string>& ColumnType::getVector() const
{
	return this->str;
}
