#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void writeInExcel(const std::string& title, const std::vector<std::string>columns, 
				  const std::string& nameFile = "result.csv");