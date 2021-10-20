/*
Люди стоят в очереди, но никогда не уходят из её начала, зато могут
приходить в конец и уходить оттуда. Более того, иногда некоторые люди
могут прекращать и начинать беспокоиться из-за того, что очередь не
продвигается.

Будем считать, что люди в очереди нумеруются целыми числами, начиная с 0.

Реализуйте обработку следующих операций над очередью:

WORRY i: пометить i-го человека с начала очереди как беспокоящегося;
QUIET i: пометить i-го человека как успокоившегося;
COME k: добавить k спокойных человек в конец очереди;
COME -k: убрать k человек из конца очереди;
WORRY_COUNT: узнать количество беспокоящихся людей в очереди.

Изначально очередь пуста.

Формат ввода
Количество операций Q, затем описания операций.
Для каждой операции WORRY i и QUIET i гарантируется, что человек с
номером i существует в очереди на момент операции.

Для каждой операции COME -k гарантируется, что k не больше текущего
размера очереди.

Формат вывода
Для каждой операции WORRY_COUNT выведите одно целое число — количество беспокоящихся людей в очереди.
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int q;
  cin >> q;
  vector<bool> is_nervous;

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "WORRY_COUNT") {

      // подсчитываем количество элементов в векторе is_nervous, равных true
      cout << count(begin(is_nervous), end(is_nervous), true) << endl;

    } else {
      if (operation_code == "WORRY" || operation_code == "QUIET") {

        int person_index;
        cin >> person_index;

        // выражение в скобках имеет тип bool и равно true для запроса WORRY,
        // поэтому is_nervous[person_index] станет равным false или true
        // в зависимости от operation_code
        is_nervous[person_index] = (operation_code == "WORRY");

      } else if (operation_code == "COME") {

        int person_count;
        cin >> person_count;

        // метод resize может как уменьшать размер вектора, так и увеличивать,
        // поэтому специально рассматривать случаи с положительным
        // и отрицательным person_count не нужно
        is_nervous.resize(is_nervous.size() + person_count, false);

      }
    }
  }

  return 0;
}
