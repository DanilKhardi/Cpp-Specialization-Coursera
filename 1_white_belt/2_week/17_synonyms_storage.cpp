/*
Два слова называются синонимами друг друга, если они имеют похожие значения.
Реализуйте следующие операции над словарём синонимов:

	ADD word1 word2 — добавить в словарь пару синонимов (word1, word2).

	COUNT word — узнать количество синонимов слова word.

	CHECK word1 word2 — проверить, являются ли слова word1 и word2 синонимами.

Слова word1 и word2 считаются синонимами, если среди запросов ADD был хотя
бы один запрос ADD word1 word2 или ADD word2 word1.

Для каждого запроса в соответствующей строке выведите ответ на него:

В ответ на запрос COUNT word выведите единственное целое число — количество
синонимов слова word.

В ответ на запрос CHECK word1 word2 выведите строку YES, если word1 и word2
являются синонимами, и NO в противном случае. */


#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {
  int q;
  cin >> q;

  map<string, set<string>> synonyms;

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "ADD") {

      string first_word, second_word;
      cin >> first_word >> second_word;

      // второе слово добавляем в список синонимов первого...
      synonyms[first_word].insert(second_word);
      // и наоборот
      synonyms[second_word].insert(first_word);

    } else if (operation_code == "COUNT") {

      string word;
      cin >> word;
      cout << synonyms[word].size() << endl;

    } else if (operation_code == "CHECK") {

      string first_word, second_word;
      cin >> first_word >> second_word;

      // ищём второе слово во множестве синонимов первого
      // (можно было сделать и наоборот)
      if (synonyms[first_word].count(second_word) == 1) {
        cout << "YES" << endl;
      } else {
        cout << "NO" << endl;
      }

    }
  }

  return 0;
}
