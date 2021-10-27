/*
Часть 5

	Наконец, вам нужно реализовать возможность использовать объекты класса
Rational в качестве элементов контейнера set и ключей в контейнере map.
*/


#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <numeric>
using namespace std;

class Rational {
public:
    Rational() {
        // конструктор по умолчанию
    	p = 0;
    	q = 1;
    }

    Rational(const int numerator, int denominator) {
        // конструктор
    	const int commin_div = gcd(numerator, denominator);
    	p = numerator / commin_div; // сокращение числителя на НОД
    	q = denominator / commin_div; // сокращение знаменателя на НОД
    	if (q < 0){ // знаменатель д.б. положительным
    		p = -p;
    		q = -q;
    	}
    }

    int Numerator() const {
    	// возвращает числитель
    	return p;
    }

    int Denominator() const {
    	// возращает знаменатель
    	return q;
    }

private:
    int p;
    int q;
};

// Вставьте сюда реализацию operator == для класса Rational из второй части
bool operator==(const Rational& lhs, const Rational& rhs) {
	// т.к. дроби сокращены, для их сравнения достаточно сравнить
	// числитель и знаменатель
	if (lhs.Numerator() == rhs.Numerator() &&
			lhs.Denominator() == rhs.Denominator()){
		return true;
	}
	return false;
}

// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а

bool operator< (const Rational& lhs, const Rational& rhs){
	return ((lhs.Numerator() * rhs.Denominator() -
			rhs.Numerator() * lhs.Denominator()) < 0);
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
