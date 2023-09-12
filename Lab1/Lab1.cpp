#define _USE_MATH_DEFINES
#include <iostream>
#include <random>
#include <Windows.h>
#include <cmath>


int randAB(int min, int max);
void FillRand(int arr[], int size, int min, int max);
void FillUp(int arr[], int size, int min, int max);
void FillDown(int arr[], int size, int min, int max);
void fillSawtoot(int arr[], int size, int min, int max, int interval);
void fillSin(int arr[], int size, int min, int max, int interval);

void printArr(int arr[], int size, int interval);


void printInterval(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		std::cout << arr[i]<<std::endl;
	}
	std::cout << std::endl;
}
void printArr(int arr[], int size,int interval)
{
	int L = size / interval;
	for (int i = 0; i < interval; i++)
	{
		printInterval(&arr[L * i], L);
	}
	
}
int randAB(int min, int max) 
{
	return (((rand())<<15)|rand()) 
			%(max-min) + min;
}
void FillRand(int arr[], int size, int min, int max)
{
	for(int i =0;i<size;i++)
		arr[i] = randAB(min, max);
}
void FillUp(int arr[], int size, int min, int max) 
{
	double h = (double(max - min)) / size;
	for (int i = 0; i < size; i++)
		arr[i] = h * i + min;
}

void FillDown(int arr[], int size, int min, int max) 
{
	FillUp(arr, size, max, min);
}
void fillSawtoot(int arr[], int size, int min, int max,int interval)
{
	int L = size / interval,j=0;

	for (int i = 0; i < interval; i++) 
		FillUp(&arr[L * i], L, min, max);

	
	if ((L * interval) < size) 
	{
		double h =  (((double(max - min))) / (L));
		for (int i = L * interval; i < size; i++,j++)
			arr[i] = h * j + min;
	}
}
void fillSin(int arr[], int size, int min, int max, int interval) {
	fillSawtoot(arr, size, min, max, interval);
	int L = size / interval;
	for (int i = 0; i <= interval; i++)
		if (i % 2 == 0)
			std::reverse(arr + (L * i), arr + (L * i) + L);
}
void fillQuaisie(int arr[], int size, int min, int max, int interval) {
	int L = size / interval, j = 0;
	for (int i = 0; i < interval; i++)
	{
		if(i >0)
			min = arr[(L * i)-1]+1;
		FillUp(&arr[L * i], L, min, max);
	}
	if ((L * interval) < size) {
		double h = (((double(max - min))) / (L));
		for (int i = L * interval; i < size; i++, j++)
			arr[i] = h * j + min;
	}
	 j = 1;
	for (int i = 0; i < interval; i++,j++)
	{
		int stepLeft =  (L * (j))-1;
		std::swap(arr[ stepLeft], arr[stepLeft + 1]);
	}
}
inline void fillRandStep(int arr[], int size, int min, int max, int interval) {
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
int main()
{
	constexpr long MAX_LENGTH = 400000000;
	int  * arr = new int[MAX_LENGTH];
	for (int N = MAX_LENGTH / 200; N <= MAX_LENGTH / 20; N += MAX_LENGTH / 200)
	{
		int t1 = GetTickCount();
		fillQuaisie(arr, N, 2, N,10);
		std::cout << (GetTickCount() - t1)<<std::endl;
	}

	return 0;

}

