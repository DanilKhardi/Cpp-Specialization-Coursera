/*
Определите до конца тела классов, соблюдая следующие требования:

Класс Dog должен являться наследником класса Animal.

Конструктор класса Dog должен принимать параметр типа string и
инициализировать им поле Name в классе Animal.
*/

#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    // ваш код
	Animal(string s) : Name(s) {
	}

    const string Name;
};


class Dog : public Animal {
public:
    // ваш код
	Dog(string s) : Animal(s){

	}

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main() {
	Dog d("Jack");
	d.Bark();
	return 0;
}
