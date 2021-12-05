/*
Решите задачу «Имена и фамилии — 1» более эффективно, использовав двоичный
поиск в методе Person::GetFullName. Напомним условие задачи.

Реализуйте класс для человека, поддерживающий историю изменений человеком
своих фамилии и имени.

Считайте, что в каждый год может произойти не более одного изменения фамилии
и не более одного изменения имени. При этом с течением времени могут открываться
всё новые факты из прошлого человека, поэтому года́ в последовательных вызовах
методов ChangeLastName и ChangeFirstName не обязаны возрастать.

	► ! Гарантируется, что все имена и фамилии непусты.

Строка, возвращаемая методом GetFullName, должна содержать разделённые одним
пробелом имя и фамилию человека по состоянию на конец данного года.

	► Если к данному году не случилось ни одного изменения
	фамилии и имени, верните строку "Incognito".

	► Если к данному году случилось изменение фамилии, но не было
	ни одного изменения имени, верните "last_name with unknown first name".

	► Если к данному году случилось изменение имени, но не было ни одного
	изменения фамилии, верните "first_name with unknown last name".
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

string FindNameByYear(const map<int, string>& m, int year) {
	string result;
	auto it_first_greater = m.upper_bound(year);
	if (it_first_greater != m.begin()) {
		result = (--it_first_greater)->second;
	}
	return result;
}


class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		year_for_name_[year] = first_name;
	}

	void ChangeLastName(int year, const string& last_name) {
		year_for_surname_[year] = last_name;
	}

	string GetFullName(int year) {
		const string first_name = FindNameByYear(year_for_name_, year);
		const string last_name = FindNameByYear(year_for_surname_, year);

		if (first_name.empty() && last_name.empty()) {
			return "Incognito";
		} else if (first_name.empty()) {
			return last_name + " with unknown first name";
		} else if (last_name.empty()) {
			return first_name + " with unknown last name";
		} else {
			return first_name + " " + last_name;
		}
	}

private:
	map<int, string> year_for_name_;
	map<int, string> year_for_surname_;
};


int main() {
	  Person person;

	  person.ChangeFirstName(1965, "Polina");
	  person.ChangeLastName(1967, "Sergeeva");
	  for (int year : {1900, 1965, 1990}) {
	    cout << person.GetFullName(year) << endl;
	  }

	  person.ChangeFirstName(1970, "Appolinaria");
	  for (int year : {1969, 1970}) {
	    cout << person.GetFullName(year) << endl;
	  }

	  person.ChangeLastName(1968, "Volkova");
	  for (int year : {1969, 1970}) {
	    cout << person.GetFullName(year) << endl;
	  }

	  return 0;
}
