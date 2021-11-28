/*
Напишите шаблонную функцию MergeSort, принимающую два итератора шаблонного
типа RandomIt и сортирующую заданный ими диапазон с помощью сортировки слиянием.
Гарантируется, что:

	► итераторы типа RandomIt аналогичны по функциональности итераторам вектора и строки,
	то есть их можно сравнивать с помощью операторов <, <=, > и >=, а также вычитать и
	складывать с числами;

	► сортируемые объекты можно сравнивать с помощью оператора <.

	template <typename RandomIt>
	void MergeSort(RandomIt range_begin, RandomIt range_end);


						▬▬▬ Алгоритм ▬▬▬
Классический алгоритм сортировки слиянием выглядит следующим образом:

	► Если диапазон содержит меньше 2 элементов, выйти из функции.

	► Создать вектор, содержащий все элементы текущего диапазона.

	► Разбить вектор на две равные части. (В этой задаче гарантируется,
	что длина передаваемого диапазона является степенью двойки, так что
	вектор всегда можно разбить на две равные части.)

	► Вызвать функцию MergeSort от каждой половины вектора.

	► С помощью алгоритма std::merge слить отсортированные половины,
	записав полученный отсортированный диапазон вместо исходного.


! Вы должны реализовать именно этот алгоритм и никакой другой: тестирующая
система будет проверять, что вы выполняете с элементами именно эти действия.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	// 1. Если диапазон содержит меньше 2 элементов, выходим из функции
	if (range_end - range_begin < 2) {
		return;
	}

	// 2. Создаем вектор, содержащий все элементы текущего диапазона
	// Тип элементов вектора узнаем из итератора следующим образом
	vector<typename RandomIt::value_type> elements(range_begin, range_end);

	// 3. Разбиваем вектор на две равные части
	size_t middle = elements.size() / 2;
	auto middle_it = elements.begin() + middle;

	// 4. Вызываем функцию MergeSort от каждой половины вектора
	MergeSort(elements.begin(), middle_it);
	MergeSort(middle_it, elements.end());

	// 5. С помощью алгоритма merge сливаем отсортированные половины
	// в исходный диапазон
	// merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
	merge(elements.begin(), middle_it, middle_it, elements.end(), range_begin);


}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
