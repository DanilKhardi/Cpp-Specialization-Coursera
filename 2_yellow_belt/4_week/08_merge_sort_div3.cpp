/*
Реализуйте сортировку слиянием, разбивая диапазон на 3 равные части, а не на 2.
Гарантируется, что длина исходного диапазона является степенью 3.

Соответственно, пункты 3–5 алгоритма нужно заменить следующими:

	► Разбить вектор на 3 равные части.

	► Вызвать функцию MergeSort от каждой части вектора.

	► Слить первые две трети вектора с помощью алгоритма merge,
	сохранив результат во временный вектор с помощью back_inserter.

	► Слить временный вектор из предыдущего пункта с последней третью
	вектора из п. 2, записав полученный отсортированный диапазон вместо исходного.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	// 1. Если диапазон содержит меньше 2 элементов, выходим из функции
	if (range_end - range_begin < 3) {
		return;
	}

	// 2. Создаем вектор, содержащий все элементы текущего диапазона
	vector<typename RandomIt::value_type> elements(range_begin, range_end);

	// 3. Разбиваем вектор на три равные части
	auto part1 = elements.begin() + elements.size() / 3;
	auto part2 = part1 + elements.size() / 3;

	// 4. Вызываем функцию MergeSort от каждой трети вектора
	MergeSort(elements.begin(), part1);
	MergeSort(part1, part2);
	MergeSort(part2, elements.end());

	// 5. С помощью алгоритма merge cливаем первые две трети во временный вектор
	// back_inserter -> http://ru.cppreference.com/w/cpp/iterator/back_inserter
	vector<typename RandomIt::value_type> tmp;
	merge(elements.begin(), part1, part1, part2, back_inserter(tmp));

	// 6. С помощью алгоритма merge сливаем отсортированные части
	// в исходный диапазон
	// merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
	merge(tmp.begin(), tmp.end(), part2, elements.end(), range_begin);

}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
