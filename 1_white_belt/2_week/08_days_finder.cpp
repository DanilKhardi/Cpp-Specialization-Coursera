/*
Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней.
Найдите номера дней (в нумерации с нуля) со значением температуры выше
среднего арифметического за все N дней.

*/


#include <iostream>
#include <vector>
using namespace std;

int MidleTemp(const vector<int>& days, int cnt){
	int midle_temp = 0;
	for (auto x: days){
		midle_temp += x;
	}
	return midle_temp / cnt;
}

int main() {
	int N;
	cin >> N;
	vector<int> days(N);
	for (auto& i: days) {
		cin >> i;
	}
	int midle_temp = MidleTemp(days, N);
	vector<int> warm_days;
	for (int i = 0; i < N; ++i) {
		if (days[i] > midle_temp) {
			warm_days.push_back(i);
		}
	}
	cout << warm_days.size() << endl;
	for (auto i: warm_days){
		cout << i << " ";
	}
	}

