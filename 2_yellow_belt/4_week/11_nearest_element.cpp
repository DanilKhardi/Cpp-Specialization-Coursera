/*
Напишите функцию FindNearestElement, для множества целых чисел numbers и
данного числа border возвращающую итератор на элемент множества, ближайший
к border. Если ближайших элементов несколько, верните итератор на наименьший
из них.
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;


set<int>::const_iterator FindNearestElement(
		const set<int>& numbers,
		int border);

set<int>::const_iterator FindNearestElement(const set<int>& numbers,
                                            int border) {
  // Запрашиваем итератор на первый элемент, не меньший border;
  // если такого элемента нет, то мы получим numbers.end()
  // set::lower_bound ->
  // http://ru.cppreference.com/w/cpp/container/set/lower_bound
  const auto first_not_less = numbers.lower_bound(border);

  // Если множество пусто или до первого элемента не меньше border
  // нет элементов, то мы уже получили ответ
  if (first_not_less == numbers.begin()) {
    return first_not_less;
  }

  // Если элементов, не меньших border, нет и set не пуст, то достаточно взять
  // итератор на последний элемент, меньший border
  // prev -> http://ru.cppreference.com/w/cpp/iterator/prev
  const auto last_less = prev(first_not_less);
  if (first_not_less == numbers.end()) {
    return last_less;
  }

  // Разыменуем оба итератора-кандидата и выберем тот,
  // чей элемент ближе к искомому
  const bool is_left = (border - *last_less <= *first_not_less - border);
  return is_left ? last_less : first_not_less;
}


int main() {

	  set<int> numbers = {1, 4, 6};
	  cout <<
	      *FindNearestElement(numbers, 0) << " " ;
		  cout <<
	      *FindNearestElement(numbers, 3) << " ";
		  cout <<
	      *FindNearestElement(numbers, 5) << " ";
		  cout <<
	      *FindNearestElement(numbers, 6) << " ";
		  cout <<
	      *FindNearestElement(numbers, 100) << endl;

	  set<int> empty_set;

	  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
	  return 0;
}
