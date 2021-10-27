/*
Определите структуру «Студент» со следующими полями: имя, фамилия, день,месяц и год
рождения. Создайте вектор из таких структур, заполните его из входных данных и затем
по запросам выведите нужные поля. Чтение и запись данных в этой задаче производится
с использованием стандартных потоков.

	Формат ввода

	--->  Первая строка содержит одно целое число N от 0 до 10000 — число студентов.

	--->  Далее идут N строк, каждая из которых содержит две строки длиной от 1 до
	15 символов — имя и фамилию очередного студента, и три целых числа от 0
	до 1000000000 — день, месяц и год рождения.

	---> Следующая строка содержит одно целое число M от 0 до 10000 — число запросов.

	---> Следующие M строк содержат строку длиной от 1 до 15 символов — запрос, и целое
	число от 1 до 1000000000 — номер студента (нумерация начинается с 1).

	Формат вывода

	---> Для запроса вида name K, где K от 1 до N, выведите через пробел имя и фамилию
	 K-го студента.

	---> Для запроса вида date K, где K от 1 до N, выведите через точку день, месяц и
	год рождения K-го студента.

	---> Для остальных запросов выведите bad request.


	!NB: неверные запросы могут выходить за границы, указанные для данных.

*/


#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Student {
	string name;
	string surname;
	int day;
	int month;
	int year;
};


int main() {
	vector<Student> students_list;
	int N;
	cin >> N;
	for (int i=0; i<N; ++i){
		string nm, snm;
		int d, m, y;
		cin >> nm >> snm >> d >> m >> y;
		students_list.push_back(Student{nm, snm, d, m, y});
	}
	int M;
	cin >> M;
	for (int i=0; i<M; ++i){
		string request;
		int position;
		cin >> request >> position;
		if (request == "name" && 0 < position && position <= N){
			cout << students_list[position-1].name << " "
					<< students_list[position-1].surname;
		}
		else if (request == "date" && 0 < position && position <= N) {
			cout << students_list[position-1].day << "."
					<< students_list[position-1].month << "."
					<< students_list[position-1].year;
		}
		else cout << "bad request";
		cout << endl;
	}
}
