#include <iostream>
#include "myRandom.h"
#include <ostream>
int counter;
using namespace std;

inline int compare(const void* a, const void*  b)
{
	key_t l = *(const key_t*)a;
	key_t r = *(const key_t*)b;
	counter++;
	return l>r;
}
inline bool compare2(const key_t a, const key_t b)
{
	counter++;
	return a >b;
}
bool isSorted(const key_t arr[], int size) {
	int i = 0;
	for (; i < size - 1; i++) {
		if (arr[i] <= arr[i + 1])
			continue;
		else
			return false;
	}
	return true;
}
int Partition(key_t arr[],int start,int end)
{
	int pivot = arr[end];
	int pIndex = start;
	int i = start - 1, j = end;

	for (;;) {
		while (compare(&pivot, (void *)&arr[++i]));
		while (!compare(&pivot, (void*)&arr[--j]))
			if (j == start)
				break;
		if (i >= j)
			break;
		swap(arr[i], arr[j]);
	}
	swap(arr[end], arr[i]);
	return i;
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
void start(const std::string &funcName) {
	constexpr long MAX_LENGTH = 5000000;
	int step = MAX_LENGTH / 5;
	int prevSize = 0;
	int stableCount = 0;
	std::ofstream timeApplication, countCompare;
	timeApplication.open(funcName+"time.txt");
	countCompare.open(funcName+"count.txt");
	std::cout << "Testing sort algorithm: " << funcName<<std::endl;
	for (int N = step; N <= MAX_LENGTH; N += step)
	{
		key_t* arr = new key_t[N];
		fillRandStep(arr, N, 0, N, 9);
		auto time = GetTickCount();
		if(funcName =="qsortC")
			qsort((void*)(arr), N, sizeof(arr[0]), compare);
		else if(funcName =="qSort")
			qSort(arr, 0, N - 1);
		else if(funcName =="sort")
			sort(arr, arr + N, compare2);
		else if(funcName =="stable")
			stable_sort(arr, arr + N, compare2);
		cout << counter << ' ' << GetTickCount() - time << endl;
		writeOnFile(countCompare, std::to_string(counter) + " "+ std::to_string((GetTickCount() - time)));
		writeOnFile(timeApplication, std::to_string(N) + " " + std::to_string((GetTickCount() - time)));
		if (isSorted(arr, N))
			stableCount++;
		counter = 0;
		delete[]arr;
	}
	if (stableCount == 5)
		std::cout << funcName << " is stable" << endl;

}
int main()
{
	system("chcp 1251 > null");
	start("qSort");
	start("qsortC");
	start("sort");
	start("stable");

	
	return 0;
}

