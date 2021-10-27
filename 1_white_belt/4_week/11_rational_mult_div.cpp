/*
Часть 3

	Аналогично предыдущей части, реализуйте операторы * и /.
Например, следующий код должен быть валидным:
*/


#include <iostream>
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


bool operator==(const Rational& lhs, const Rational& rhs) {
	// т.к. дроби сокращены, для их сравнения достаточно сравнить
	// числитель и знаменатель
	if (lhs.Numerator() == rhs.Numerator() &&
			lhs.Denominator() == rhs.Denominator()){
		return true;
	}
	return false;
}

Rational operator+(const Rational& lhs, const Rational& rhs){
	return Rational(
			lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
			lhs.Denominator() * rhs.Denominator()
			);
}

Rational operator-(const Rational& lhs, const Rational& rhs){
	return Rational(
				lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
				lhs.Denominator() * rhs.Denominator()
				);
}

// Реализуйте для класса Rational операторы * и /

Rational operator*(const Rational& lhs, const Rational& rhs){
	return Rational(lhs.Numerator() * rhs.Numerator(),
			lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs){
	// операцию деления можно представить как умножение на обр. дробь
	return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}


int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    const Rational r = Rational(1, 2) * Rational(1, 3) / Rational(1, 4);
    if (r == Rational(2, 3)) {
      cout << "equal" << endl;
    }

    cout << "OK" << endl;
    return 0;
}
