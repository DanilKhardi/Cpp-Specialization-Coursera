/*
В данном задании вам предстоит изменить код 04_original_code.cpp таким образом, чтобы
он соответствовал изложенным в курсе принципам.

Представьте, что этот код вам достался в наследство от коллеги и теперь вам предстоит
поддерживать его и улучшать. Первое, что вы решили сделать — это провести рефакторинг.

Конечные цели рефакторинга:

	• упростить дальнейшую поддержку кода;
	• уменьшить сложность кода;
	• упростить добавление новых абстракций в программу.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Profession {
public:
	Profession(const string& name, const string& type)
	: Name(name), Type(type)
	{
	}

	const string Name, Type;

public:
	virtual void Walk(const string& destination) const {
        cout << Type <<": " << Name << " walks to: " << destination << endl;
	}
};


class Student : public Profession {
public:
    Student(const string& name, const string& favouriteSong)
    : Profession(name, "Student"), FavouriteSong(favouriteSong)
    {
    }

    void Learn() const {cout << Type <<": " << Name << " learns" << endl;}

    void Walk(const string& destination) const override {
        cout << Type << ": " << Name << " walks to: " << destination << endl;
        cout << Type <<": " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() const {cout << Type <<": " << Name << " sings a song: " << FavouriteSong << endl;}

public:
    const string FavouriteSong;
};


class Teacher : public Profession {
public:
    Teacher(const string& name, const string& subject)
    : Profession(name, "Teacher"), Subject(subject)
    {
    }

    void Teach() const {cout << Type <<": " << Name << " teaches: " << Subject << endl;}

public:
    const string Subject;
};


class Policeman : public Profession {
public:
    Policeman(const string& name)
    : Profession(name, "Policeman")
    {
    }

    void Check(const Profession& p) const {
        cout << Type << ": " << Name << " checks " << p.Type << "." << p.Type << "'s name is: " << p.Name << endl;
    }
};

void VisitPlaces(Profession& prof, vector<string> places) {
	for (auto p : places) {
		prof.Walk(p);
	}
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
