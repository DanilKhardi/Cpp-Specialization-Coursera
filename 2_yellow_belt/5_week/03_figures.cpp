/*
Вам дана функция main, которая считывает из стандартного ввода команды по работе
с набором геометрических фигур.


Как видно из кода, есть два вида команд:
	• ADD — добавить фигуру в набор;
	• PRINT — для каждой фигуры в наборе распечатать название, периметр и площадь.


Программа поддерживает три вида фигур: прямоугольник, треугольник и круг.
Их добавление описывается так:

	► ADD RECT width height —  добавить прямоугольник с размерами
	width и height (например, ADD RECT 2 3).

	► ADD TRIANGLE a b c —  добавить треугольник со сторонами a, b и c
	(например, ADD TRIANGLE 3 4 5).

	► ADD CIRCLE r —  добавить круг радиуса r (например, ADD CIRCLE 5).

________________________________________________________________________________
				Пример работы программы

				►►► Ввод
				ADD RECT 2 3
				ADD TRIANGLE 3 4 5
				ADD RECT 10 20
				ADD CIRCLE 5
				PRINT

				◄◄◄ Вывод
				RECT 10.000 6.000
				TRIANGLE 12.000 6.000
				RECT 60.000 200.000
				CIRCLE 31.400 78.500
________________________________________________________________________________

Не меняя функцию main, реализуйте недостающие функции и классы:

	• базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;

	• классы Triangle, Rect и Circle, которые являются наследниками класса Figure
	  и переопределяют его виртуальные методы;

	• функцию CreateFigure, которая в зависимости от содержимого входного потока
	  создаёт shared_ptr<Rect>, shared_ptr<Triangle> или shared_ptr<Circle>.


Гарантируется, что размеры всех фигур — это натуральные числа не больше 1000.
В качестве значения PI используйте 3,14.


*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <istream>
#include <iomanip>
#include <cmath>
using namespace std;

double PI = 3.14;


/*Базовый класс*/
class Figure {
public:
	/*Определяем интерфейс с помощью виртуальных методов*/
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;

};


class Triangle : public Figure {
public:
	Triangle(double a, double b, double c)
	: x(a), y(b), z(c)
	{}

	string Name() const override {
		return "TRIANGLE";
	}

	double Perimeter() const override {
		return x + y + z;
	}

	double Area() const override {
		double p;
		p = Perimeter() / 2;
		return sqrt(p * (p - x) * (p - y) * (p - z));
	}

private:
	const double x, y, z;
};


class Rect : public Figure {
public:
	Rect(double a, double b)
	: x(a), y(b)
	{}

	string Name() const override {
		return "RECT";
	}

	double Perimeter() const override {
		return (x + y) * 2;
	}

	double Area() const override {
		return x * y;
	}

private:
	const double x, y;
};


class Circle : public Figure {
public:
	Circle(double a)
	: r(a)
	{}

	string Name() const override {
		return "CIRCLE";
	}

	double Perimeter() const override {
		return 2 * PI * r;
	}

	double Area() const override {
		return PI * r * r;
	}

private:
	const double r;
};


shared_ptr<Figure> CreateFigure(istringstream& is) {
	shared_ptr<Figure> fig;
	string type;
	double a, b, c;
	is >> type;
	if (type == "TRIANGLE") {
		is >> a >> b >> c;
		fig = make_shared<Triangle>(a, b, c);
	} else if (type == "RECT") {
		is >> a >> b;
		fig = make_shared<Rect>(a, b);
	} else if (type == "CIRCLE") {
		is >> a;
		fig = make_shared<Circle>(a);
	}
	return fig;
};


int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
