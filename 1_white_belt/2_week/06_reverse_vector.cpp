/*
Реализуйте функцию void Reverse(vector<int>& v),
которая переставляет элементы вектора в обратном
порядке.
*/


#include <vector>
#include <iostream>
using namespace std;

void Reverse(vector<int>& v) {
	vector<int> tmp = v;
	for (int i = tmp.size() - 1; i >= 0; --i) {
		v[tmp.size() - i - 1] = tmp[i];
	}
}


int main() {
	vector<int> numbers = {1, 5, 3, 4, 2};
	Reverse(numbers);
	for (auto i: numbers) {
		cout << i << " ";
	}
}
