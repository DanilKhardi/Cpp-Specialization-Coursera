/*
Реализуйте класс, поддерживающий набор строк в отсортированном порядке.
Класс должен содержать два публичных метода:
*/


#include <vector>
#include <iostream>
#include <string>
#include<set>
#include<algorithm>
using namespace std;

class SortedStrings {
public:
	void AddString(const string& s){
		words.push_back(s);
	}
	vector<string> GetSortedStrings() {
		sort(begin(words), end(words));
		return words;
	}
private:
	vector<string> words;
};

//void PrintSortedStrings(SortedStrings& strings) {
//  for (const string& s : strings.GetSortedStrings()) {
//    cout << s << " ";
//  }
//  cout << endl;
//}
//
//int main() {
//	SortedStrings strings;
//
//	strings.AddString("first");
//	strings.AddString("third");
//	strings.AddString("second");
//	PrintSortedStrings(strings);
//
//	strings.AddString("second");
//	PrintSortedStrings(strings);
//
//	return 0;
//}
