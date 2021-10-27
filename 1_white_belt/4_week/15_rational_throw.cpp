/*
Поменяйте реализацию конструктора класса Rational так, чтобы он выбрасывал
исключение invalid_argument, если знаменатель  равен нулю. Кроме того,
переделайте реализацию оператора деления для класса Rational так, чтобы он 
выбрасывал исключение domain_error, если делитель равен нулю.  
*/


#include <iostream>
#include <exception>
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
    	if (denominator == 0){
    		throw invalid_argument("denominator == 0 !!!");
    	}
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

Rational operator/(const Rational& lhs, const Rational& rhs){
	if (lhs.Denominator() == 0 || rhs.Numerator() == 0){
		throw domain_error("err div 0");
	}
	// операцию деления можно представить как умножение на обр. дробь
	return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
