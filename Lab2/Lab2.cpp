#include <iostream>
#include "myRandom.h"
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
int main()
{
	system("chcp 1251 > null");
	constexpr long MAX_LENGTH = 5000000;
	//key_t  * arr = new key_t[MAX_LENGTH];
	int step = MAX_LENGTH/5;
	int prevSize=0;

	for (int N = step; N <= MAX_LENGTH; N +=step)
	{
		key_t* arr = new key_t[N];
		fillRandStep(arr, N, 0, N,9);

		auto time = GetTickCount();
		//qSort(arr, 0, N-1);
		//qsort((void *)(arr), N, sizeof(arr[0]), compare);
		//stable_sort(arr, arr+N,compare2);
		sort(arr, arr + N, compare2);


		cout << counter << ' ' << GetTickCount() - time << endl;
		//cout << "Counter : " << counter<<endl;
		counter = 0;
		delete []arr;
	}
	//std::cout << counter;
	return 0;
}

