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
void printArr(int arr[], int size);



void printArr(int arr[], int size)
{
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << std::endl;
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
	for (int i = 0; i < size; i++)
	{
		double h = (double(max - min)) / size; 
		arr[i] = h * i + min;
	}
}

void FillDown(int arr[], int size, int min, int max) 
{
	FillUp(arr, size, max, min);
}
void fillSawtoot(int arr[], int size, int min, int max,int interval)
{
	int L = size / interval;
	for (int i = 0; i < interval; i++) {
		FillUp(&arr[L * i], L, min, max);
	}
	if ((L * interval) < size) {
		double h =  (((double(max - min))) * interval / (size));
		for (int i = L * interval; i < size; i++)
			arr[i] = h * (i-L*interval) + min;
	}
	//printArr(arr, size);
}
void fillSin(int arr[], int size, int min, int max, int interval) {
	fillSawtoot(arr, size, min, max, interval);
	int L = size / interval;
	for (int i = 0; i < interval; i++)
		if (i % 2 == 0)
			std::reverse(arr + (L * i), arr + (L * i) + L);
}
void fillQuaisie(int arr[], int size, int min, int max, int interval) {
	
}
void fillRandStep(int arr[], int size, int min, int max, int interval) {
	int L = size / interval;
	double h = (double(max - min)) / size;
	for (int i = 0; i < size; i++) {
		arr[i] = randAB(min, min + (max / interval));
		if ((i + 1) % (size / interval) == 0)
			min += max / interval;
	}
	if ((L * interval) < size) {
		double h = (((double(max - min))) * interval / (size));
		for (int i = L * interval; i < size; i++)
			arr[i] = h * (i - L * interval) + min;
	}
}
int main()
{
	const int MAX_LENGTH = 1000000;
	int  * arr = new int[MAX_LENGTH];
	/*for (int N = MAX_LENGTH / 10; N <= MAX_LENGTH; N += MAX_LENGTH / 10)
	{
		int t1 = GetTickCount();
		FillUp(arr, MAX_LENGTH, 1, 20);
		std::cout << GetTickCount() - t1<<std::endl;
	}*/
	//fillSawtoot(arr, 11, 1, 10,5);
	/*FillUp(arr, 10, 1, 10);
	printArr(arr, 10);*/
	/*fillSawtoot(arr, 20, 1, 10, 3);
	std::cout << "FillSawtooh" << std::endl;
	printArr(arr, 20);
	std::cout << std::endl;
	fillSin(arr, 20, 1, 10, 3);
	printArr(arr, 20);*/
	fillRandStep(arr, 10, 1, 10, 2);
	printArr(arr, 10);
	return 0;

}

