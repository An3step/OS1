#include "../Employee.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUSSIAN");
    if (argc < 3)
    {
        std::cout << "Incorrect arguments number\n";
        return 2;
    }
    employee Emp;
    std::ifstream checkFile;
    std::ofstream File;
    std::string n_argv = std::string(argv[2]);
    argc = std::stoi(argv[1]);
    if(argc < 1)
    {
        std::cout << "Incorrect records number\n";
        return 1;
    }
    try
    {
        checkFile.open(n_argv);
        if (checkFile)
        {
            std::wcerr << "Error: File '" << argv[2] << "' exists already\n" << std::endl;
            checkFile.close();
            return 1;
        }
        checkFile.close();
        File.open(n_argv, std::ios::binary);
        for (int i = 0; i < argc; i++)
        {
            std::cout << "Number - ";
            std::cin >> Emp.num;
            std::cout << "Name - ";
            std::cin >> Emp.name;
            std::cout << "Hours - ";
            std::cin >> Emp.hours;
            File.write(reinterpret_cast<const char*>(&Emp), sizeof(Emp));
        }
        File.close();
    }
     catch (std::ofstream::failure& e)
    {
        std::cerr << "Error working with file\n";
        if (checkFile.is_open())
        {
            checkFile.close();
        }
        if (File.is_open())
        {
            File.close();
        }
        return 1;
    }
    return 0;
}