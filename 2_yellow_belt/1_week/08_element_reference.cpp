/*
Реализуйте шаблонную функцию GetRefStrict, которая на вход принимает: map и
значение ключа k. Если элемент по ключу k в коллекции отсутствует, то функция
должна бросить исключение runtime_error, иначе вернуть ссылку на элемент в
коллекции.

Пример использования функции
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
*/

#include <iostream>
#include <string>
#include <map>
#include <exception>
using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, Key k) {
	if (m.count(k) == 0) {
		throw runtime_error("No such key in dictionary");
	}
	Value& result_value = m[k];
	return result_value;
}

int main() {
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl;
	return 0;
}
