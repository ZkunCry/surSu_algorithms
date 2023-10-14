#include "WriteEx.h"

void writeInExcel(const std::string& title, const std::vector<std::string>columns, const std::string& nameFile = "result.csv")
{
    std::ofstream file(nameFile);
    file << title << std::endl;
    for (auto value : columns) 
        file << value << std::endl;

    file.close();
}