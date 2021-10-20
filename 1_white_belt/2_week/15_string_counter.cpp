//Дан набор строк. Найдите количество уникальных строк в этом наборе.

#include<set>
#include <iostream>
#include<string>
using namespace std;

int main() {
	set<string> unique_strings;
	string s;
	int N;
	cin >> N;
	for (int i=0; i<N; ++i){
		cin >> s;
		unique_strings.insert(s);
	}
	cout << unique_strings.size();
}
