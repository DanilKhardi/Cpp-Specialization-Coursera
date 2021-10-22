/*
Дополните класс из предыдущей задачи «Имена и фамилии — 1» методом GetFullNameWithHistory:
В отличие от метода GetFullName, метод GetFullNameWithHistory должен вернуть не только
последние имя и фамилию к концу данного года, но ещё и все предыдущие имена и фамилии в
обратном хронологическом порядке. Если текущие факты говорят о том, что человек два раза
подряд изменил фамилию или имя на одно и то же, второе изменение при формировании истории
нужно игнорировать.
*/


#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;


struct PersonData{
	string name = "";
	string surname = "";
};


class Person {
public:

	void ChangeFirstName(int year, const string& first_name){
		person_storage_data[year].name = first_name;
	}

	void ChangeLastName(int year, const string& last_name){
		person_storage_data[year].surname = last_name;
	}

	string GetFullName(int year){
		for (const auto& i: person_storage_data){
			if (i.first > year) return "Incognito";
			break;
		}
		if (!person_storage_data.size()) return "Incognito";
		else {
			string res_name = "";
			string res_surname = "";
			for (const auto& i: person_storage_data){
				if (i.first <= year && i.second.name != "") res_name = i.second.name;
				if (i.first <= year && i.second.surname != "") res_surname = i.second.surname;
			}
			if (res_surname == "") return res_name + " with unknown last name";
			else if (res_name == "") return res_surname + " with unknown first name";
			else return res_name + " " + res_surname;
		}
	}

	string GetFullNameWithHistory(int year){
		for (const auto& i: person_storage_data){
			if (i.first > year) return "Incognito";
			break;
		}
		if (person_storage_data.empty()) return "Incognito";
		else {
			vector<string> names_history;
			vector<string> surnames_history;
			for (auto& i: person_storage_data ){
				if (i.first <= year && i.second.name != "") names_history.push_back(i.second.name);
				if (i.first <= year && i.second.surname != "") surnames_history.push_back(i.second.surname);
			}
			string result = GetRightFormatStringForResult(names_history, surnames_history);
			return result;
		}
	}

private:
	map<int, PersonData> person_storage_data;

	string GetRightFormatStringForResult(vector<string>& names_history, vector<string> surnames_history){
		// Функция возвращает строку необходимого формата

		if (names_history.empty() && !surnames_history.empty()) return GetJointedString(surnames_history) +
				" with unknown first name";
		else if (surnames_history.empty() && !names_history.empty()) return GetJointedString(names_history) +
				" with unknown last name";
		else return GetJointedString(names_history) + " " + GetJointedString(surnames_history);
	}

	string GetJointedString(vector<string>& data){
		// Преобразует вектор строк в строку заданного формата
		vector<string> new_data = DeleteDuplicateDataAndReverse(data);
		string result = new_data[0];
		if (new_data.size() == 1) return result;
		else {
			for (int i=1; i<new_data.size(); ++i){
				if (i == 1) result += " (" + new_data[i];
				else if (i >= 2) result += ", " + new_data[i];
				if (i == new_data.size()-1) result += ")";
			}
		}
		return result;
	}

	vector<string> DeleteDuplicateDataAndReverse(vector<string>& data){
		// Удалаяет дублирующиеся элементы-соседи и разворачивает вектор-строк
		vector<string> new_data;
		if (data.size() == 1) new_data.push_back(data[0]);
		else {
			reverse(begin(data), end(data));
			new_data.push_back(data[0]);
			for (int i=1; i<data.size(); ++i){
				if (data[i-1] != data[i]) new_data.push_back(data[i]);
			}
		}
		return new_data;
	}

};

int main() {
//	***  testing code  ***

    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova"); //-Sergeeva
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    for (int year : {1960, 1967, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1901, "Polina");
    person.ChangeLastName(1901, "Sergeeva");
    for (int year : {1900, 1960, 1967, 1990, 1991}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }


    return 0;
}
