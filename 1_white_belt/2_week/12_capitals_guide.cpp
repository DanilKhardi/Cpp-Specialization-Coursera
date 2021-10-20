/*
Реализуйте справочник столиц стран.

На вход программе поступают следующие запросы:

	CHANGE_CAPITAL country new_capital — изменение столицы страны country на new_capital,
	либо добавление такой страны с такой столицей, если раньше её не было.

	RENAME old_country_name new_country_name — переименование страны из
	old_country_name в new_country_name.

	ABOUT country — вывод столицы страны country.

	DUMP — вывод столиц всех стран.

Формат ввода
В первой строке содержится количество запросов Q, в следующих Q строках — описания запросов.
Все названия стран и столиц состоят лишь из латинских букв, цифр и символов подчёркивания.

Формат вывода
Выведите результат обработки каждого запроса:

В ответ на запрос CHANGE_CAPITAL country new_capital выведите

	— Introduce new country country with capital new_capital, если страны country раньше
	не существовало;

	— Country country hasn't changed its capital, если страна country до текущего момента
	имела столицу new_capital;

	— Country country has changed its capital from old_capital to new_capital, если страна
	country до текущего момента имела столицу old_capital, название которой не совпадает
	с названием new_capital.


В ответ на запрос RENAME old_country_name new_country_name выведите
	— Incorrect rename, skip, если новое название страны совпадает со старым, страна
	old_country_name не существует или страна new_country_name уже существует;

	— Country old_country_name with capital capital has been renamed to new_country_name,
	если запрос корректен и страна имеет столицу capital.

В ответ на запрос ABOUT country выведите
	— Country country doesn't exist, если страны с названием country не существует;

	— Country country has capital capital, если страна country существует и имеет столицу capital.

В ответ на запрос DUMP выведите
	— There are no countries in the world, если пока не было добавлено ни одной страны;

	— последовательность пар вида country/capital, описывающую столицы всех стран, если
	в мире уже есть хотя бы одна страна. При выводе последовательности пары указанного
	вида необходимо упорядочить по названию страны и разделять между собой пробелом.*/


#include<string>
#include <iostream>
#include<map>
using namespace std;

void Change_Capital(map<string, string>& map_capitals,
					const string& country, const string& new_capital) {
	string result;
	if (map_capitals.count(country) == 0) {
		map_capitals[country] = new_capital;
		cout << "Introduce new country " << country <<
				" with capital " << new_capital;
	}
	else if (map_capitals[country] == new_capital) {
		cout << "Country " << country << " hasn't changed its capital";
	}
	else if (map_capitals[country] != new_capital) {
		cout << "Country " << country << " has changed its capital from " <<
				map_capitals[country] << " to " << new_capital;
		map_capitals[country] = new_capital;
	}
}


void Rename(map<string, string>& map_capitals,
		const string& old_country_name, const string& new_country_name){
	if (old_country_name == new_country_name ||
	(!map_capitals.count(old_country_name) || map_capitals.count(new_country_name))) {
		cout << "Incorrect rename, skip";
	}
	else if (map_capitals.count(old_country_name)) {
		cout << "Country " << old_country_name << " with capital " <<
				map_capitals[old_country_name] << " has been renamed to " << new_country_name;
		map_capitals[new_country_name] = map_capitals[old_country_name];
		map_capitals.erase(old_country_name);

	}
}


void About(map<string, string>& map_capitals, const string& country){
	if (!map_capitals.count(country)) {
		cout << "Country " << country << " doesn't exist";
	}
	else {
		cout << "Country " << country << " has capital " << map_capitals[country];
	}
}


void Dump(const map<string, string>& map_capitals){
	if (!map_capitals.size()) {
		cout << "There are no countries in the world";
	}
	else {
		for (const auto& item : map_capitals){
			cout << item.first << "/" << item.second << " ";
		}
	}

}

int main() {
	int Q;
	map<string, string> map_capitals;
	cin >> Q;
	for (int i= 0; i < Q; ++i) {
		string command;
		cin >> command;
		if (command == "CHANGE_CAPITAL") {
			string country, new_capital;
			cin >> country >> new_capital;
			Change_Capital(map_capitals, country, new_capital);
			cout << endl;
		}
		else if (command == "RENAME") {
			string old_country_name, new_country_name;
			cin >> old_country_name >> new_country_name;
			Rename(map_capitals, old_country_name, new_country_name);
			cout << endl;
		}
		else if (command == "ABOUT"){
			string country;
			cin >> country;
			About(map_capitals, country);
			cout << endl;
		}
		else if (command == "DUMP") {
			Dump(map_capitals);
			cout << endl;
		}
	 }
}
