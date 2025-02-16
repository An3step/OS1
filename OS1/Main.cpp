#include <iostream>
#include <fstream>
#include <string>
#include "Employee.h"
#include "windows.h"
#include "conio.h"
#include <vector>
#include <cstring>
#define UNICODE // Используем Unicode
#define WIN32_LEAN_AND_MEAN // Уменьшаем размер Windows API

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    std::string report;
    std::string file;
    std::cout << "Введите имя бинарного файла\n";
    std::cin >> file;
    file += ".bin";
    std::cout << "Введите количество записей\n";
    int argc;
    std::cin >> argc;
    std::string str = "Creator/Creator.exe " + std::to_string(argc) + " " + file;
    size_t size_needed = mbstowcs(nullptr, str.c_str(), 0);
    wchar_t* wstr = new wchar_t[size_needed + 1];
    mbstowcs(wstr, str.c_str(), size_needed + 1);

    STARTUPINFOW si;
    PROCESS_INFORMATION piCom;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&piCom, sizeof(piCom));
    if(!CreateProcessW(NULL, wstr, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCom))
    {
        std::wcerr << "Ошибка при создании процесса\n";
        CloseHandle(piCom.hProcess);
        CloseHandle(piCom.hThread);
        return 1;
    }
    // Ждем завершения процесса
    WaitForSingleObject(piCom.hProcess, INFINITE);
    // Закрываем ручки
    CloseHandle(piCom.hProcess);
    CloseHandle(piCom.hThread);
    
    std::cout << "Содержимое бинарного файла\n";
    std::vector<employee> employers;
    employee Emp;
    std::ifstream ReaderFile;
    try
    {
        ReaderFile.open(file, std::ios::binary);
        while(ReaderFile.read(reinterpret_cast<char*>(&Emp), sizeof(Emp)))
        {
            employers.push_back(Emp);
        }
        ReaderFile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        ReaderFile.close();
        return 2;
    }
    for(int i = 0; i < employers.size(); i++)
    {
        std::cout << "Номер: " << employers[i].num << ", Имя: " << employers[i].name
        << ", Часы: " << employers[i].hours << '\n';
    }
    std::cout << "Введите имя файла отчёта\n";
    std::cin >> report;
    report += ".txt";
    double payment;
    std::cout << "Введите плату\n";
    std::cin >> payment;
    str = "Reporter/Reporter.exe " + file + " " + report + " " + std::to_string(payment);
    size_needed = mbstowcs(nullptr, str.c_str(), 0);
    delete wstr;
    wstr = new wchar_t[size_needed + 1];
    mbstowcs(wstr, str.c_str(), size_needed + 1);
    ZeroMemory(&si, sizeof(si));
    if(!CreateProcessW(NULL, wstr, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCom))
    {
        std::wcerr << "Ошибка при создании процесса\n";
        CloseHandle(piCom.hProcess);
        CloseHandle(piCom.hThread);
        return 1;
    }
    // Ждем завершения процесса
    WaitForSingleObject(piCom.hProcess, INFINITE);

    // Закрываем ручки
    CloseHandle(piCom.hProcess);
    CloseHandle(piCom.hThread);
    try
    {
        ReaderFile.open(report);
        std::string boop;
        ReaderFile >> boop >> boop >> boop >> boop;
        int q = 0;
        while(ReaderFile >> boop)
        {
            ReaderFile >> boop;
            boop.pop_back();
            Emp.num = std::stoi(boop);
            ReaderFile >> boop >> boop;
            boop.pop_back();
            std::strcpy(Emp.name, boop.c_str());
            ReaderFile >> boop >> boop;
            boop.pop_back();
            Emp.hours = std::stod(boop);
            ReaderFile >> boop >> boop;
            payment = std::stod(boop);
            std::cout << "Номер: " << Emp.num << ", Имя: " << Emp.name
            << ", Часы: " << Emp.hours << ", Зарплата: " << payment << '\n';
        }
        ReaderFile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        ReaderFile.close();
        return 2;
    }
    return 0;
}