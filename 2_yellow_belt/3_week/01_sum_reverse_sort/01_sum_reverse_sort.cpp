/*
Вам дан заголовочный файл sum_reverse_sort.h, содержащий
объявления трёх функций.

Вам надо прислать cpp-файл, содержащий определения этих
функций.

Функции должны складывать два числа, обращать строку и
сортировать вектор чисел по возрастанию соотвественно.
*/

#include <iostream>
#include <algorithm>
using namespace std;

#include "sum_reverse_sort.h" // load interface functions

// Implementation func sum_reverse_sort.h

int Sum(int x, int y) {
	return x + y;
}

string Reverse(string s) {
	string reverse_s = "";
	for (size_t i = s.length(); i >= 1; --i) {
		reverse_s += s[i - 1];
	}
	return reverse_s;
}

void Sort(vector<int>& nums) {
	sort(nums.begin(), nums.end());
}

int main() {
	// testing code
	cout << Sum(1, 2) << endl;
	cout << Reverse("hello") << endl;
	vector<int> a = {-5, 2, 0, -2, 4, 1, 3};
	Sort(a);
	for (const auto& i : a) {
		cout << i << ' ';
	}
	return 0;
}
