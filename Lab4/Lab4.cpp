
#include <iostream>
#include <functional>
#include <fstream>
#include <Windows.h>
#include <string>
#include <sstream>
using std::endl;
using std::cout;
using std::string;

typedef struct methodHorner {
public:
	int Q = 256; //Необходимо для избежания больших чисел хэша
	int B = 13;
}hash_var;

static hash_var variables;

/*По формуле: Hash = c1 * b^m-1 + c2 * b^m-2 + ... +  cm * b^0 */


long int get_hash(const string& src) {
	
	int result = 0;
	for (auto value : src)
		result = (variables.B * result + char(value)) % variables.Q;
	return result;
}
int search_pattern(const string& src, const string& pattern) {
	int multiplier = 1,count = 0;
	for (int i = 1; i < pattern.length(); i++) {
		multiplier = (multiplier * variables.B) % variables.Q;
	}
	auto pattern_hash = get_hash(pattern);
	auto src_hash = get_hash(src.substr(0,pattern.length()));
	
	for (int i = 0; i < (src.length() - pattern.length()) + 1;i++)
	{
		if (pattern_hash == src_hash)
		{
			if (src.substr(i,  pattern.length()) == pattern)
				count++;
		}
		if (i < (src.length() - pattern.length())) {
			src_hash = ((src_hash - char(src[i]) * multiplier) * variables.B + char(src[i + pattern.length()])) % variables.Q;
			if (src_hash < 0)
				src_hash += variables.Q;
		}
	}
	
	return count >0 ? count : -1;

}

int main()
{
	std::ifstream in("text.txt");
	std::stringstream ss;
	ss << in.rdbuf();
	
	string text;
	text = ss.str();
	in.close();

	const int N_MAX = text.size();
	const int Step = N_MAX / 5;
	auto tempN = 0;
	int d = 10;
	for (int N = Step; N <= N_MAX; N += Step)
	{
		auto mainText = text.substr(0, N);
		auto patternText = mainText.substr(tempN, d);
		auto time = GetTickCount();
		auto result = search_pattern(text, patternText);
		cout << GetTickCount() - time <<" "<<mainText.size() << endl;
		cout << "Result: " << result << endl;
		d *= 10;
		tempN = N;
	}

}
