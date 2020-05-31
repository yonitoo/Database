#include<iostream>
#include <fstream>

#include "Database.h"
#include "Helper.h"

int main()
{
    Database database;
    std::fstream file;
    file.open("Catalogue.txt", std::fstream::in);
    file.seekg(0, file.beg);
    database.read(file);
    file.close();
    database.showtables();
    database.print("test");
    database.select(1, "ivan", "test");
    std::cout << database.count("test", 1, "ivan");
    //database.import("test2.txt");

    std::string command;
    std::fstream currentFile;
    std::string currentFileName;
    std::string currentstring;
    std::pair<bool, std::string> isOpen = { false, "" };
    while (std::getline(std::cin, command))
    {
        std::vector<std::string> words = splitLine(command);
        //open
        if (words.size() >= 1 && words[0] == "open")
        {
            if (words.size() > 2 || isOpen.first == true)
            {
                continue;
            }
            currentFileName = words[1];
            currentFile.open(currentFileName, std::fstream::in);
            currentFile.seekg(0, currentFile.beg);
            isOpen.first = true;
            isOpen.second = currentFileName;
            if (database.read(currentFile))
            {
                std::cout << "Successfully opened " << currentFileName << std::endl;
            }
            else
            {
                std::cout << "Reading failed!" << std::endl;
            }
        }
        //close
        else if (words.size() == 1 && words[0] == "close")
        {
            if (isOpen.first == false)
            {
                continue;
            }
            isOpen.first = false;
            currentFile.close();
            database.erase();
            std::cout << "successfully closed " << currentFileName << std::endl;
        }
        //save
        else if (words.size() == 1 && words[0] == "save")
        {
            if (!isOpen.first)
            {
                continue;
            }
            currentFile.open(currentFileName, std::fstream::out);
            database.write(currentFile);
            currentFile.close();
            std::cout << "successfully saved " << currentFileName << std::endl;
        }
        //save as
        else if (words.size() >= 2 && words[0] == "save" && words[1] == "as")
        {
            if (words.size > 3)
            {
                continue;
            }
            std::fstream in;
            in.open(words[2], std::fstream::out);
            in.seekg(0, in.beg);
            database.write(in);
            in.close();
            std::cout << "successfully saved as" << words[2] << std::endl;
        }
        //help
        else if (words.size() == 1 && words[0] == "help")
        {
            std::cout << "The following commands are supported :" << std::endl;
            std::cout << "open <currentFile>     opens <currentFile>" << std::endl;
            std::cout << "close           closes currently opened currentFile" << std::endl;
            std::cout << "saveas <currentFile>   saves the currently open currentFile in <currentFile>" << std::endl;
            std::cout << "help            prints this information" << std::endl;
            std::cout << "exit            exists the program" << std::endl;
        }
        //exit
        else if (words.size() == 1 && words[0] == "exit")
        {
            std::cout << "Exiting the program..." << std::endl;
            return 0;
        }
    }
    return 0;
}
