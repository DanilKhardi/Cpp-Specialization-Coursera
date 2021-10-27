/*
Часть 4

	В этой части вам нужно реализовать операторы ввода и вывода для класса Rational.
В результате у вас должен работать, например, такой код
*/


#include <iostream>
#include <sstream>
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

// Реализуйте для класса Rational операторы << и >>

istream& operator >> (istream& stream, Rational& r) {
    int p, q;
    char opr;
    if (stream >> p && stream >> opr && stream >> q) {
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
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
        	cout << r1.Numerator() << " " << r1.Denominator()<< endl;
        	cout << r2.Numerator() << " " << r2.Denominator() << endl;

            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    cout << "OK" << endl;
    return 0;
}
