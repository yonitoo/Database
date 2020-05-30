#include<iostream>
#include <fstream>

#include "Database.h"

void menu()
{
    //switch open, saveas, vsichki komandi
}

int main()
{
    Database database;
    std::fstream file;
    file.open("dbtest.txt", std::fstream::in);
    file.seekg(0, file.beg);
    database.read(file);
    file.close();
    return 0;
}
