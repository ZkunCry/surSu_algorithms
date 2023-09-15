#define _USE_MATH_DEFINES
#define VAR_TYPE 		double // Necessary for real and integer numbers
#include <iostream>
#include <random>
#include <Windows.h>
#include <cmath>
#include <fstream>
#include <ostream>
#include <string>
#include <format>
using namespace std;
typedef VAR_TYPE key_t;

int randAB(int min, int max);
void FillRand(key_t arr[], int size, key_t min, key_t max);
void FillUp(key_t arr[], int size, key_t min, key_t max);
void FillDown(key_t arr[], int size, key_t min, key_t max);
void fillSawtoot(key_t arr[], int size, key_t min, key_t max, key_t interval);
void fillSin(key_t arr[], int size, key_t min, key_t max, key_t interval);
inline void writeOnFile(std::ofstream& out, const std::string& sourceText);
void printArr(key_t arr[], int size, int interval);


void printInterval(key_t arr[], int size) {
	for (int i = 0; i < size; i++) 
		std::cout << arr[i]<<std::endl;
	std::cout << std::endl;
}

void printArr(key_t arr[], int size,int interval)
{
	int L = size / interval;
	for (int i = 0; i < interval; i++)
		printInterval(&arr[L * i], L);
	
}
int randAB(int min, int max) 
{
	return (((rand())<<15)|rand()) 
			%(max-min) + min;
}

double db_randAB(double min, double max) {
	return min + fmod(static_cast<double>(rand()), max - min);
}

void FillRand(key_t arr[], int size, key_t min, key_t max)
{
	for(int i =0;i<size;i++)
		arr[i] = (key_t)db_randAB(min, max);
}

void FillUp(key_t arr[], int size, key_t min, key_t max) 
{
	double h = (double(max - min)) / size;
	for (int i = 0; i < size; i++)
		arr[i] = h * i + min;
}

void FillDown(key_t arr[], int size, key_t min, key_t max) 
{
	FillUp(arr, size, max, min);
}
void fillSawtoot(key_t arr[], int size, key_t min, key_t max,key_t interval)
{
	int L = size / interval,j=0;
	double h = (((double(max - min))) / (L));
	for (int i = 0; i < interval; i++) 
		FillUp(&arr[L * i], L, min, max);

	if ((L * interval) < size) 
		for (int i = L * interval; i < size; i++,j++)
			arr[i] = h * j + min;
}
void fillSin(key_t arr[], int size, key_t min, key_t max, key_t interval) {
	fillSawtoot(arr, size, min, max, interval*2);
	int L = size / (interval+interval);
	for (int i = 0; i <= interval; i++)
		if (i % 2 == 0)
			std::reverse(arr + (L * i), arr + (L * i) + L);
}
void fillQuaisie(key_t arr[], int size, key_t min, key_t max, int interval) {
	int L = size / interval, j = 0;
	double h = (((double(max - min))) / (L));
	for (int i = 0; i < interval; i++)
	{
		if(i >0)
			min = arr[(L * i)-1]+1;
		FillUp(&arr[L * i], L, min, max);
	}
	if ((L * interval) < size) 
		for (int i = L * interval; i < size; i++, j++)
			arr[i] = h * j + min;
	 j = 1;
	for (int i = 0; i < interval-1; i++,j++)
	{
		int stepLeft =  (L * (j))-1;
		std::swap(arr[stepLeft], arr[stepLeft + 1]);
	}
}
inline void fillRandStep(key_t arr[], int size, key_t min, key_t max, int interval) {
	int L = size / interval;

	for (int i = 0; i < interval; i++) {
		
		FillRand(&arr[L*i],L,min,  (min + ((max / interval))));
		min += max / interval;
	}
	int j = 0;
	if ((L * interval) < size) {
		double h = abs((((double(max - min))) / L));
		for (int i = L * interval; i < size; i++,j++)
			arr[i] = h * j + min;
	}

}
inline void writeOnFile(std::ofstream &out,const std::string &sourceText) //Needed to write results to a file
{
	out << sourceText << std::endl;
}
int main()
{
	system("chcp 1251 > null");
	constexpr long MAX_LENGTH = 100000000;
	std::ofstream out;
	std::string resultIteration;
	out.open("table.txt");
	key_t  * arr = new key_t[MAX_LENGTH];
	int j = 1;

	for (int N = MAX_LENGTH / 20; N <= MAX_LENGTH; N += MAX_LENGTH / 20)
	{
		auto t1 = GetTickCount();
		FillRand(arr, N, 1, N);
		writeOnFile(out, '(' + std::to_string(N / 10000) +
			',' + std::to_string((GetTickCount() - t1)) + ')');
		std::cout << "(" << N/10000 << ','<< (GetTickCount() - t1) <<')'  << std::endl;
		j++;

	}
	return 0;
}

