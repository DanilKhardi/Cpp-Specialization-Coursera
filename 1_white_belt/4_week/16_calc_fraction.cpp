/*
	Вам надо написать программу, которая считывает из стандартного ввода одну строку
в формате ДРОБЬ_1 операция ДРОБЬ_2.  ДРОБЬ_1 и ДРОБЬ_2 имеют формат X/Y,
где X — целое, а Y — целое неотрицательное число. операция — это один из
символов '+', '-', '*', '/'.

	Если ДРОБЬ_1 или ДРОБЬ_2 является  некорректной обыкновенной дробью, ваша программа
должна вывести в  стандартный вывод сообщение "Invalid argument". Если считанная
операция — это деление на ноль,  выведите в стандартный вывод сообщение
"Division by zero". В противном случае выведите результат операции.
*/


#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <exception>
#include <numeric>
using namespace std;

class Rational {
public:
    Rational() {
    	p = 0;
    	q = 1;
    }

    Rational(const int numerator, int denominator) {
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

Rational operator*(const Rational& lhs, const Rational& rhs){
	return Rational(lhs.Numerator() * rhs.Numerator(),
			lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs){
	if (lhs.Denominator() * rhs.Numerator() == 0){
		throw domain_error("Division by zero");
	}
	// операцию деления можно представить как умножение на обр. дробь
	return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

istream& operator >> (istream& stream, Rational& r) {
    int p, q;
    char opr;
    if (stream >> p && stream >> opr && stream >> q) {
    	if (q == 0) throw invalid_argument("Invalid argument");
    	if (not p || opr != '/' || not q){
    		r = {};
    	}
    	else {
    		r = { p, q };
    	}

    }
    return stream;
}

ostream& operator<<(ostream& stream, const Rational& rational){
	stream << rational.Numerator() << "/" << rational.Denominator();
	return stream;
}


int main() {
	try{
		Rational x, y;
		char math_operation;
		cin >> x >> math_operation >> y;
		if (math_operation == '+') cout << x + y;
		else if (math_operation == '-') cout << x - y;
		else if (math_operation == '*') cout << x * y;
		else if (math_operation == '/') cout << x / y;
	} catch (exception& err) {
		cout << err.what();
	}
	return 0;
}
