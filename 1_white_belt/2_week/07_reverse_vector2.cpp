/*
Реализуйте функцию vector<int> Reversed(const vector<int>& v),
возвращающую копию вектора v, в которой числа переставлены
в обратном порядке.
*/


#include <iostream>
#include <vector>
using namespace std;

vector<int> Reversed(const vector<int>& v) {
	vector<int> v_copy = v;
	int n = v_copy.size();
	for (int i = 0; i < n / 2; ++i) {
		int tmp = v_copy[i];
		v_copy[i] = v_copy[n-1-i];
		v_copy[n-1-i] = tmp;
	}
	return v_copy;
}


int main() {
	vector<int> a = {1,5,3,4,2};
	vector<int> res = Reversed(a);
	for (auto i: res) {
		cout << i << " ";
	}
}
