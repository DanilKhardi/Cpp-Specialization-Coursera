/*
В стандартном потоке дана одна строка, состоящая из N + 1 целых чисел.
Первым числом идёт само число N. Далее следуют ещё N чисел, обозначим
их за массив A. Между собой числа разделены пробелом.
Отсортируйте массив А по модулю и выведите его в стандартный поток.*/


#include <iostream>
#include<vector>
#include<algorithm>
#include <cmath>
using namespace std;

void Print(const vector<int>& arr){
	for (auto& i: arr){
		cout << i << " ";
	}
}


int main() {
	int N;
	cin >> N;
	int num;
	vector<int> A;
	for (int i=0; i<N; ++i){
		cin >> num;
		A.push_back(num);
	}
	sort(begin(A), end(A), [](const int& x, const int& y) {return abs(x) < abs(y);});
	Print(A);
}
