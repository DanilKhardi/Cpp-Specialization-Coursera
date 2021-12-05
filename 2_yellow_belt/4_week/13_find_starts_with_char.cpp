/*
Напишите функцию FindStartsWith:

	► принимающую отсортированный набор строк в виде итераторов range_begin,
	  range_end и один символ prefix;
	► возвращающую диапазон строк, начинающихся с символа prefix, в виде пары итераторов.

Если итоговый диапазон пуст, его границы должны указывать на то место в контейнере, куда
можно без нарушения порядка сортировки вставить любую строку, начинающуюся с символа prefix
(подобно алгоритму equal_range). Гарантируется, что строки состоят лишь из строчных латинских
букв и символ prefix также является строчной латинской буквой.

Поиск должен осуществляться за логарифмическую сложность — например, с помощью двоичного поиска.


					►►► Подсказка ◄◄◄

К символам (char) можно прибавлять или вычитать числа, получая таким образом следующие или предыдущие
буквы в алфавитном порядке. Например, для строки s выражение --s[0] заменит её первую букву на предыдущую.

Обратите внимание, что выражение 'a' + 1 имеет тип int и поэтому может понадобиться привести его к типу
char с помощью static_cast.
*/

#include <algorithm>
#include <utility>
#include <string>
#include <iostream>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
		RandomIt range_begin, RandomIt range_end,
		char prefix) {

	  // Все строки, начинающиеся с '<prefix>', больше или равны строке "<prefix>"
	  auto left = lower_bound(range_begin, range_end, string(1, prefix));

	  // Составим следующий в алфавите символ.
	  // Не страшно, если prefix = 'z':
	  // в этом случае мы получим следующий за 'z' символ в таблице символов
	  char next_prefix = static_cast<char>(prefix + 1);

	  // Строка "<next_prefix>" в рамках буквенных строк
	  // является точной верхней гранью
	  // множества строк, начнающихся с '<prefix>'
	  auto right = lower_bound(range_begin, range_end, string(1, next_prefix));

	  return {left, right};
	};

int main() {
  const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

  const auto m_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
  for (auto it = m_result.first; it != m_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto p_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
  cout << (p_result.first - begin(sorted_strings)) << " " <<
      (p_result.second - begin(sorted_strings)) << endl;

  const auto z_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
  cout << (z_result.first - begin(sorted_strings)) << " " <<
      (z_result.second - begin(sorted_strings)) << endl;

  return 0;
}
