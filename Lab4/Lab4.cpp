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


int SearchStringKMP(const char* T, int N,const  char* P, int M) {
	int* Next, i, j;
	Next = (int*)malloc(M * sizeof(int));
	for (Next[0] = j = -1, i = 1; i < M; i++) {
		//Префикс-функция (индексы)
		for (; j > -1 && P[j + 1] != P[i]; j = Next[j]);
		if (P[j + 1] == P[i]) j++;
		Next[i] = j;
	}
	for (j = -1, i = 0; i < N; i++) {
		//пока есть совпадения i и j растут одновременно
		for (; j > -1 && P[j + 1] != T[i]; j = Next[j]);//сдвиги
		if (P[j + 1] == T[i]) j++;
		if (j == M - 1) { free(Next); return i - j; }
	}
	free(Next);
	return -1;
}




int main()
{
	const int MaxSizeT = 10000000000;
	const int MaxSizeP = 1000000000;
	const int Trials = 10;
	int StepT = MaxSizeT / 5;
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
			FillRand(text, N, 'A', 'Z');
			for (int i = 0; i < Trials; i++)
			{
				int id = randAB(0, N - M - 1);
				pattern = text.substr(id, M);
				pattern.pop_back();
				pattern.push_back('-');
				auto t1 = GetTickCount64();

				//int index = KMP(text,pattern);

				auto index = strstr(text.c_str(), pattern.c_str());
				auto t2 = GetTickCount64();
				time += t2 - t1;
			}
			cout << M << " " << (double)(time / Trials) << endl;
			time = 0;



		}
	//}

		cout << endl;
	
}

