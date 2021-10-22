/*
Реализуйте класс для человека, поддерживающий историю изменений
человеком своих фамилии и имени.

Считайте, что в каждый год может произойти не более одного изменения
фамилии и не более одного изменения имени. При этом с течением времени
могут открываться всё новые факты из прошлого человека, поэтому года́ в
последовательных вызовах методов ChangeLastName и ChangeFirstName не
обязаны возрастать.

Гарантируется, что все имена и фамилии непусты.
Строка, возвращаемая методом GetFullName, должна содержать разделённые
одним пробелом имя и фамилию человека по состоянию на конец данного года.

Если к данному году не случилось ни одного изменения фамилии и имени,
верните строку "Incognito".

Если к данному году случилось изменение фамилии, но не было ни одного
изменения имени, верните "last_name with unknown first name".

Если к данному году случилось изменение имени, но не было ни одного изменения
фамилии, верните "first_name with unknown last name".
*/


#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;


struct PersonData{
	string name;
	string surname;
};


class Person {

public:
	void ChangeFirstName(int year, const string& first_name){
		map_name_surname[year].name = first_name;
	}

	void ChangeLastName(int year, const string& last_name){
		map_name_surname[year].surname = last_name;
	}

	string GetFullName(int year){
		for (const auto& i: map_name_surname){
			if (i.first > year) return "Incognito";
			break;
		}
		if (!map_name_surname.size()) return "Incognito";
		else {
			string res_name = "";
			string res_surname = "";
			for (const auto& i: map_name_surname){
				if (i.first <= year && i.second.name != "") res_name = i.second.name;
				if (i.first <= year && i.second.surname != "") res_surname = i.second.surname;
			}
			if (res_name == "") return res_surname + " with unknown first name";
			else if (res_surname == "") return res_name + " with unknown last name";
			else return res_name + " " + res_surname;
		}
		}
private:

	map<int, PersonData> map_name_surname;
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

