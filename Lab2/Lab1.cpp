#define _USE_MATH_DEFINES
#define VAR_TYPE 		int // Necessary for real and integer numbers
#include <iostream>
#include <random>
#include <Windows.h>
#include <cmath>
#include <fstream>
#include <ostream>
#include <string>
#include <algorithm>
#include <functional>

int counter;
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
		swap(arr[stepLeft], arr[stepLeft + 1]);
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


inline const bool compare(key_t a, key_t b)
{
	counter++;
	return a >= b;
}

int Partition(key_t arr[],int start,int end)
{
	int pivot = arr[end];
	int pIndex = start;
	for (int i = start; i < end; i++)

		if (compare(arr[i], pivot)) {
			swap(arr[i], arr[pIndex]);
			pIndex++;
		}
	swap(arr[pIndex], arr[end]);
	return pIndex;
}
inline void qSort(key_t arr[], int start,int end)
{
	if (end - start <=0)
		return;
	int pivot = Partition(arr, start, end);
	if ((pivot - start) > (end - pivot))
	{
		qSort(arr, pivot + 1, end);
		qSort(arr, start, pivot - 1);
	}
	else
	{
		qSort(arr, start, pivot - 1);
		qSort(arr, pivot + 1, end);
	}
	
}
int main()
{
	system("chcp 1251 > null");
	constexpr long MAX_LENGTH =1000000;
	key_t  * arr = new key_t[MAX_LENGTH];
	int step = MAX_LENGTH / 5;
	int prevSize=0;
	FillRand(arr, MAX_LENGTH, 1, 100);
	for (int N = step; N <= MAX_LENGTH; N += step)
	{
		//std::cout << "prevSize: " << prevSize << " N: " << N << endl;
		auto time = GetTickCount();
		//stable_sort(arr + prevSize, arr + N);
		qSort(arr, prevSize, N);
		//sort(arr + prevSize, arr + N);
		prevSize = N;
		
		cout << N<<' '<< GetTickCount() - time << endl;
	}
	std::cout << counter;
	return 0;
}

