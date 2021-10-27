/*
Часть 2

	Реализуйте для класса Rational операторы ==, + и - так, чтобы операции с
дробями можно было записывать естественным образом. Например, следующий
код должен быть валидным:
 * */


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


// Реализуйте для класса Rational операторы ==, + и -


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


int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
