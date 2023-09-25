#include <iostream>
#include <cmath>
#include "myRandom.h"

using key_t = int;
static uint64_t cmp = 0;

int findJump(key_t* arr, const size_t len, const key_t& value);
int findDirect(key_t* arr, const size_t len, const key_t& value);
int findBinary(key_t* arr, const size_t len, const key_t& value);



int findDirect(key_t* arr, const size_t len, const key_t& value)
{
	for (int i = 0; i < len; i++)
	{
		if (arr[i] == value)
			return i;
		cmp++;
	}
	return -1;
}

int findJump(key_t* arr, const size_t len, const key_t& value)
{
	int arrLen = len;
	int jumpStep = (int)sqrt(len);
	int previousStep = 0;
	cmp++;
	while (arr[min(jumpStep, arrLen) - 1] < value)
	{
		previousStep = jumpStep;
		jumpStep += (int)(sqrt(arrLen));
		cmp++;
		if (previousStep >= arrLen)
			return -1;
	}
	cmp++;
	while (arr[previousStep] < value) {
		cmp++;
		previousStep++;
		if (previousStep == min(jumpStep, arrLen))
			return -1;
	}
	if (arr[previousStep] == value)
		return previousStep;
	return -1;
}


int findBinary(key_t* arr, const size_t len, const key_t& value)
{
	int first = 0;
	int last = len - 1;
	while (first <= last) {
		cmp++;
		int mid = (first + last) / 2;
		if (arr[mid] == value)
			return mid;
		else if (arr[mid] < value)
			first = mid + 1;
		else if (arr[mid] > value)
			last = mid - 1;
	}
	return -1;
}


int main()
{
	key_t arr[] = { 0,3,5,10,20,40,50,70,100 };
	int arrSize = sizeof(arr) / sizeof(arr[0]);
	const long long N_MAX = 1000000;
	const int iterations = 500;
	const auto Step = N_MAX / 5;
	int(*typeSearch[3])(key_t*, const size_t, const key_t&) = {
		findDirect,
		findBinary,
		findJump
	};
	std::string searchName[3] = {
		"findDirect",
		"findBinary",
		"findJump"
	};
	for (int f = 0; f < 3; f++)
	{
		std::cout <<"------------" << searchName[f] << "------------" <<std::endl;
		for (auto N = 10; N <= N_MAX; N *= 2)
		{
			key_t* arr = new key_t[N];
			fillRandStep(arr, N, 0, N, 1);
			std::stable_sort(arr, arr + N);
			uint64_t cmpSum = 0;
			for (int j = 0; j < iterations; j++)
			{
				cmp = 0;
				int index = ((rand() << 15) | rand()) % N;
				if (typeSearch[f](arr, N, arr[index]) != -1) {
					cmpSum += cmp;
				}
			}
			std::cout << N << " " << cmpSum / iterations << std::endl;
			delete[]arr;
		}
	}

}
