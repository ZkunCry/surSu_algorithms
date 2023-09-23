#include <iostream>
#include <cmath>

using key_t = int;

int findJump(key_t* arr, const size_t len, const key_t& value);
int findDirect(key_t* arr, const size_t len, const key_t& value);
int findBinary(key_t* arr, const size_t len, const key_t& value);



int findJump(key_t* arr, const size_t len, const key_t& value)
{
	for (int i = 0; i < len; i++)
		if (arr[i] == value)
			return i;
	return -1;
}

int findDirect(key_t* arr, const size_t len, const key_t& value)
{
	int arrLen = len;
	int jumpStep = (int)sqrt(len);
	int previousStep = 0;
	while (arr[std::min(jumpStep, arrLen) - 1] < value)
	{
		previousStep = jumpStep;
		jumpStep += (int)(sqrt(arrLen));
		if (previousStep >= arrLen)
			return -1;
	}
	while (arr[previousStep] < value) {
		previousStep++;
		if (previousStep == std::min(jumpStep, arrLen))
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

}
