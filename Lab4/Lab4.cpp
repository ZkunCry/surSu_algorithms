#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm> 
using std::endl;
using std::cout;
using std::string;


int randAB(int min, int max)
{
	return (((rand()) << 15) | rand())
		% (max - min) + min;
}
double db_randAB(double min, double max) {
	return min + fmod(static_cast<double>(rand()), max - min);
}

template <typename _T>
void FillRand(_T &src, int size, char min, char max)
{
	for (int i = 0; i < size; i++)
		src.push_back(randAB(min, max));
}
typedef struct methodHorner {
public:
	int Q = 256; //Необходимо для избежания больших чисел хэша
	int B = 13;
}hash_var;

int SearchStringKMP(string text, string pattern) {

	int i, j;
	std::vector<int> Next(pattern.length());
	int M = pattern.length();
	int N = text.length();
	for (Next[0] = j = -1, i = 1; i < M; i++) {
		//Префикс-функция (индексы)
		for (; j > -1 && pattern[j + 1] != pattern[i]; j = Next[j]);
		if (pattern[j + 1] == pattern[i]) j++;
		Next[i] = j;
	}
	for (j = -1, i = 0; i < N; i++) {
		//пока есть совпадения i и j растут одновременно
		for (; j > -1 && pattern[j + 1] != text[i]; j = Next[j]);//сдвиги
		if (pattern[j + 1] == text[i]) j++;
		if (j == M - 1) {  return i - j; }
	}

	return -1;
}



int main()
{
	const int MaxSizeT = 10000000;
	const int MaxSizeP = 1000000;
	const int Trials = 5;
	int StepT = MaxSizeT / 10;
	int StepP = MaxSizeP / 5;
	int N = MaxSizeT; 
	int M = MaxSizeP;
	string text;
	string pattern;
	ULONGLONG time=0;
	cout << "-------------------------Search algorithm KMP-------------------------" << endl;


	/*for (int N = StepT; N <= MaxSizeT; N += StepT)
	{*/


		for (int M = StepP; M <= MaxSizeP; M += StepP)
		{
			pattern.clear();
			text.clear();
			FillRand(text, N, 'a', 'z');
			for (int i = 0; i < Trials; i++)
			{
				int id = randAB(0, N - M - 1);
				pattern = text.substr(id, M);
				/*pattern.pop_back();
				pattern.push_back('-');*/
				auto t1 = GetTickCount64();

				//int index = KMP(text,pattern);

				auto index = strstr(text.c_str(), pattern.c_str());
			/*	if (index == -1)
					cout << "false";*/
				auto t2 = GetTickCount64();
				time += t2 - t1;
			}
			cout << M << " " << (double)(time / Trials) << endl;
			time = 0;



		}
	//}

		cout << endl;
	
}

