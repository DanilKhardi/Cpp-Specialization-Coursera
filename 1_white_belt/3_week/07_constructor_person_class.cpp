/*
Дополните класс Person из задачи «Имена и фамилии — 2» конструктором,
позволяющим задать имя и фамилию человека при рождении, а также сам год
рождения. Класс не должен иметь конструктора по умолчанию.

При получении на вход года, который меньше года рождения:
методы GetFullName и GetFullNameWithHistory должны
отдавать "No person";

методы ChangeFirstName и ChangeLastName должны игнорировать запрос.

Кроме того, необходимо объявить константными все методы, которые
по сути ими являются.
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
	Person(const string& name, const string& surname, int year){
		year_birth = year;
		person_storage_data[year_birth] = {name, surname};
		for (auto& i: person_storage_data){
			if (i.first < year) person_storage_data.erase(i.first);
		}

	}

	void ChangeFirstName(int year, const string& first_name){
		if (year >= year_birth) person_storage_data[year].name = first_name;
	}

	void ChangeLastName(int year, const string& last_name){
		if (year >= year_birth) person_storage_data[year].surname = last_name;
	}

	string GetFullName(int year) const {
		for (const auto& i: person_storage_data){
			if (i.first > year) return "No person";
			break;
		}
		if (!person_storage_data.size()) return "No person";
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

	string GetFullNameWithHistory(int year) const {
		for (const auto& i: person_storage_data){
			if (i.first > year) return "No person";
			break;
		}
		if (person_storage_data.empty()) return "No person";
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
	int year_birth;
	map<int, PersonData> person_storage_data;

	string GetRightFormatStringForResult(vector<string>& names_history, vector<string> surnames_history) const
	{
		if (names_history.empty() && !surnames_history.empty()) return GetJointedString(surnames_history) +
				" with unknown first name";
		else if (surnames_history.empty() && !names_history.empty()) return GetJointedString(names_history) +
				" with unknown last name";
		else return GetJointedString(names_history) + " " + GetJointedString(surnames_history);
	}

	string GetJointedString(vector<string>& data) const{
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

	vector<string> DeleteDuplicateDataAndReverse(vector<string>& data) const{
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
	// testing code
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}
