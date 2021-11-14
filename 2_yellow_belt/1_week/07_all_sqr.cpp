/*
Реализуйте шаблонную функцию Sqr, которая работает не только для чисел,
но и для контейнеров. Функция должна возвращать копию исходного контейнера,
модифицировав его следующим образом:

	► для vector элементы нужно возвести в квадрат;
	► для map в квадрат нужно возвести только значения, но не ключи;
	► для pair в квадрат нужно возвести каждый элемент пары.

Функция должна корректно работать не только для контейнеров, состоящих из
чисел, но и для составных объектов, например, векторов словарей пар чисел.

Для успешной сдачи решения необходимо сделать предварительное объявление
шаблонных функций перед всеми шаблонными функциями. Зачем это нужно и как
это работает вы узнаете далее из наших курсов.
*/


#include <iostream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

// Предварительное объявление шаблонных функций
template<typename T> T Sqr(const T& x);
template<typename Item> vector<Item> Sqr(const vector<Item>& v);
template<typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m);
template<typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p);


template<typename T>
T Sqr(const T& x){
	T x_new = x * x;
	return x_new;
}

template<typename Item>
vector<Item> Sqr(const vector<Item>& v) {
	vector<Item> v_new;
	for (const auto& i : v){
	    // Здесь важно, что вместо i * i вызывается функция Sqr:
	    // это позволяет возводить в квадрат составные объекты
		v_new.push_back(Sqr(i));
	}
	return v_new;
}

template<typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m){
	map<Key, Value> m_new;
	for (const auto& i : m){
		m_new[i.first] = Sqr(i.second);
	}
	return m_new;
}

template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
	return {Sqr(p.first), Sqr(p.second)};
}


int main() {
	// Пример вызова функции
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
	  cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
	  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}

