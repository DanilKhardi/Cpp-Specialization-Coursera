
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;


void PrintPermutations (const int& N) {
	vector<int> permutations(N);

	  // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
	  // Заполняет диапазон последовательно возрастающими значениями
	  // Обратные итераторы позволяют заполнить его, двигаясь от конца к началу
	  // т.е элементы в векторе упорядочены по возрастанию
	iota(permutations.rbegin(), permutations.rend(), 1);

	do {
		for (auto number : permutations) {
			cout << number << ' ';
		}
		cout << endl;

		  // prev_permutation ->
		  //     http://ru.cppreference.com/w/cpp/algorithm/prev_permutation
		  // Преобразует диапазон в предыдущую (лексикографически) перестановку,
		  // если она существует, и возвращает true,
		  // иначе (если не существует) - в последнюю (наибольшую) и возвращает false
	} while (prev_permutation(permutations.begin(), permutations.end()));
}

int main() {
	int N;
	cin >> N;
	PrintPermutations(N);
	return 0;
}
