/*
В стандартном потоке дана одна строка, состоящая из числа N
и следующих за ним N строк S. Между собой число и строки
разделены пробелом.
Отсортируйте строки S в лексикографическом порядке по
 возрастанию, игнорируя регистр букв, и выведите их в
 стандартный поток вывода.
 */

#include<algorithm>
#include<vector>
#include <iostream>
using namespace std;

void Printer(const vector<string>& x){
	for (const auto& i: x){
		cout << i << " ";
	}
}

string str_to_low(const string& s){
	string result;
	for (auto i: s){
		result += tolower(i);
	}
	return result;
}

bool srt(string x, string y){
	return str_to_low(x) < str_to_low(y);
}


int main() {
	int N;
	cin >> N;
	string S;
	vector<string> arrStr;
	for (int i=0; i<N; ++i){
		cin >> S;
		arrStr.push_back(S);
	}
	sort(begin(arrStr), end(arrStr), srt);
	Printer(arrStr);

	}
