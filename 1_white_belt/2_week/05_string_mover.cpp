/*
Напишите функцию MoveStrings, которая принимает два вектора строк,
source и destination, и дописывает все строки из первого вектора
в конец второго. После выполнения функции вектор source должен
оказаться пустым.
*/


#include <vector>
#include<string>
#include <iostream>
using namespace std;


void MoveStrings(vector<string>& source, vector<string>& destination) {
	for (auto i: source) {
		destination.push_back(i);
	}
	source.clear();
}

int main() {
	vector<string> source = {"a", "b", "c"};
	vector<string> destination = {"z"};
	MoveStrings(source, destination);
	for (auto i: destination){
		cout << i << " ";
	}
}
