#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <iomanip>
#include <exception>


using namespace std;


class Date {
public:

  Date(const int& new_year, const int& new_month, const int& new_day){

	  year = new_year;

      if (new_month  < 1  || new_month > 12) {
          throw invalid_argument("Month value is invalid: " + to_string(new_month));
      }
	  month = new_month;

	  if (new_day < 1 || new_day > 31) {
		  throw invalid_argument("Day value is invalid: " + to_string(new_day));
	  }
	  day = new_day;
  }

  int GetYear() const{
	  return year;
  }

  int GetMonth() const{
	  return month;
  }

  int GetDay() const{
	  return day;
  }

private:
  int year, month, day;
};


// для сравнения дат и использования их в качестве ключей
// переопределим оператор меньше
bool operator<(const Date& lhs, const Date& rhs){
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
			vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

// настройка кастомного вывода для даты
ostream& operator<< (ostream& out, const Date& date ) {
	  cout << setw(4) << setfill('0') << date.GetYear()
					<< '-' << setw(2) << setfill('0') << date.GetMonth()
					<< '-' << setw(2) << setfill('0') << date.GetDay();
	  return out;
}


class Database {
public:

  void AddEvent(const Date& date, const string& event){
	  base_events[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event){
	  if (base_events[date].count(event)) {
		 base_events[date].erase(event) ;
		 return true;
	  }
	  return false;
  }

  int DeleteDate(const Date& date){
	  if (base_events.count(date)){
		  int length = base_events[date].size();
		  base_events.erase(date);
		  return length;
	  } else {
		  return 0;
	  }
  }

  void Find(const Date& date) const{
	  if (base_events.count(date)){
		  set<string> events_value = base_events.at(date);
		  for (const auto& event: events_value) {
			  cout << event << endl;
		  }
	  }
  }

  void Print() const{
	  if (not base_events.empty()) {
		  for (const auto& pair: base_events) {
			  for (const auto& event: pair.second){
				  cout << pair.first << " " << event << endl;
			  }
		  }
	  }
  }

private:
  map<Date, set<string>> base_events;

};


Date split_date(const string& date){

	istringstream input_stream(date);
	bool correct = true;

	int year, month, day;

	correct = correct && (input_stream >> year);
	correct = correct && (input_stream.peek() == '-');
	input_stream.ignore(1);

	correct = correct && (input_stream >> month);
	correct = correct && (input_stream.peek() == '-');
	input_stream.ignore(1);

	correct = correct && (input_stream >> day);
	correct = correct && input_stream.eof();

	if (!correct) {
		throw invalid_argument("Wrong date format: " + date);
	}
	return Date(year, month, day);
	}


int main() {
	try {
		Database db;

		  string command;
		  while (getline(cin, command)) {
		    // Считайте команды с потока ввода и обработайте каждую
			  stringstream input(command);
			  string operation, date_str, event;
			  input >> operation;
			  if (operation == "Add") {
				  input.ignore(1);
				  input >> date_str;
				  try{
					  Date date = split_date(date_str);
					  input.ignore(1);
					  input >> event;
					  db.AddEvent(date, event);
				  } catch (invalid_argument& err) {
					cout << err.what();
					break;
				}
			  }
			  else if (operation == "Del"){
				  input.ignore(1);
				  input >> date_str;
				  try {
					  Date date = split_date(date_str);
					  input.ignore(1);
					  if (input >> event){
						  if(db.DeleteEvent(date, event)){
							  cout << "Deleted successfully" << endl;
						  } else {
							  cout << "Event not found" << endl;
						  }
					  }
					  else {
						  int length = db.DeleteDate(date);
						  cout << "Deleted " + to_string(length) +
								  " events" << endl;
					  }
				  } catch (invalid_argument& err) {
					cout << err.what();
					break;
				}

			  }
			  else if (operation == "Find"){
				  input.ignore(1);
				  input >> date_str;
				  try {
					 Date date = split_date(date_str);
					 db.Find(date);
				  } catch (invalid_argument& err) {
					  cout << err.what();
					  break;
				}

			  }
			  else if (operation == "Print"){
				  db.Print();
			  }
			  else if (operation == "") {

			  }
			  else {
				  cout << "Unknown command: "  << operation;
			  }
		  }
	}
	catch (exception& err) {
		cout << err.what() << endl;
	}
	return 0;

}
