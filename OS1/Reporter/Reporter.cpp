#include "../Employee.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUSSIAN");
    if (argc < 4)
    {
        std::cout << "Incorrect arguments number\n";
        return 2;
    }
    std::string source = argv[1];
    std::string report = argv[2];
    double payment = std::stod(argv[3]);
    std::ifstream file;
    std::vector<employee> employers;
    employee Emp;
    try
    {
        file.open(source, std::ios::binary);
        while(file.read(reinterpret_cast<char*>(&Emp), sizeof(Emp)))
        {
            employers.push_back(Emp);
        }
        file.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        file.close();
        return 2;
    }
    
    std::ofstream reporting;
    try
    {
        reporting.open(report);
        reporting << "\tОтчёт по файлу " << source << '\n';
        for(int i = 0; i < employers.size(); i++)
        {
            reporting << "Номер: " << employers[i].num << ", Имя: " << employers[i].name
             << ", Часы: " << employers[i].hours << ", Зарплата: " << employers[i].hours * payment << '\n';
        }
        reporting.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        reporting.close();
        return 2;
    }
    return 0;
}