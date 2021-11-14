/*
Имеется база регионов, представленная вектором структур Region.
Lang — идентификатор языка.

Напишите функцию FindMaxRepetitionCount, принимающую базу регионов и
определяющую, какое максимальное количество повторов (число вхождений
одного и того же элемента) она содержит. Две записи (объекты типа Region)
считаются различными, если они отличаются хотя бы одним полем.

Если все записи уникальны, считайте максимальное количество повторов равным 1.
Если записи отсутствуют, верните 0. Гарантируется, что типа int достаточно для
хранения ответа.
*/


#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

enum class Lang {
  DE, FR, IT
};

bool operator<(const Region& rhs, const Region& lhs){
	return tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population) <
			tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions){
	int result = 0;
	map<Region, int> repetition_count;
	for (const auto& region: regions){
		result = max(result, ++repetition_count[region]);
	}
	return result;
}

int main() {
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      },
  }) << endl;

  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Toulouse",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          31
      },
  }) << endl;

  return 0;
}
