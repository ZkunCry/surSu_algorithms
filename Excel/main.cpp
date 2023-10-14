#include <iostream>
#include "WriteEx.h"
int main()
{
    const std::string title = "example;test;test2";
    std::vector<std::string> columns = { "1;2;3","4;5;6","7;8;9" };
    writeInExcel(title, columns);
    return 0;
}