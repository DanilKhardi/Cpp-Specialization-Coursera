/*
¬ этой задаче вам нужно разработать классы SmsNotifier и EmailNotifier, отправл€ющие уведомлени€
в виде SMS и e-mail соответственно, а также абстрактный базовый класс дл€ них.

¬ам даны функции SendSms и SendEmail, которые моделируют отправку SMS и e-mail.
	Х void SendSms(const string& number, const string& message);
	Х void SendEmail(const string& email, const string& message);


__________________________________–азработайте:_______________________________________________

1. јбстрактный базовый класс INotifier, у которого будет один чисто виртуальный
метод void Notify(const string& message).

2.  ласс SmsNotifier, который:

	Х €вл€етс€ потомком класса INotifier;
	Х в конструкторе принимает один параметр типа string Ч номер телефона;
	Х переопредел€ет метод Notify и вызывает из него функцию SendSms.

3.  ласс EmailNotifier, который:

	Х €вл€етс€ потомком класса INotifier;
	Х в конструкторе принимает один параметр типа string Ч адрес электронной почты;
	Х переопредел€ет метод Notify и вызывает из него функцию SendEmail.

*/

#include <string>
#include <iostream>
using namespace std;


void SendSms(const string& number, const string& message) {
	cout << "Send '" << message << "' to number " << number << endl;
}
void SendEmail(const string& email, const string& message) {
	cout << "Send '" << message << "' to e-mail " << email << endl;
}

class INotifier {
public:
	virtual void Notify(const string& message) const = 0;
};


class SmsNotifier: public INotifier {
public:
	SmsNotifier(const string& number)
		: number_(number)
	{
	}
	void Notify(const string& message) const override {
		SendSms(number_, message);
	}
private:
	const string number_;
};


class EmailNotifier: public INotifier {
public:
	EmailNotifier(const string& email)
		: email_(email)
	{
	}
	void Notify(const string& message) const override {
		SendEmail(email_, message);
	}
private:
	string email_;
};


void Notify(INotifier& notifier, const string& message) {
	notifier.Notify(message);
}


int main() {
	SmsNotifier sms{"+7-495-777-77-77"};
	EmailNotifier email{"na-derevnyu@dedushke.ru"};

	Notify(sms, "I have White belt in C++");
	Notify(email, "And want a Yellow one");

	return 0;
}
