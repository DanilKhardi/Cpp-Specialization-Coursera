/*
� ���� ������ ��� ����� ����������� ������ SmsNotifier � EmailNotifier, ������������ �����������
� ���� SMS � e-mail ��������������, � ����� ����������� ������� ����� ��� ���.

��� ���� ������� SendSms � SendEmail, ������� ���������� �������� SMS � e-mail.
	� void SendSms(const string& number, const string& message);
	� void SendEmail(const string& email, const string& message);


__________________________________������������:_______________________________________________

1. ����������� ������� ����� INotifier, � �������� ����� ���� ����� �����������
����� void Notify(const string& message).

2. ����� SmsNotifier, �������:

	� �������� �������� ������ INotifier;
	� � ������������ ��������� ���� �������� ���� string � ����� ��������;
	� �������������� ����� Notify � �������� �� ���� ������� SendSms.

3. ����� EmailNotifier, �������:

	� �������� �������� ������ INotifier;
	� � ������������ ��������� ���� �������� ���� string � ����� ����������� �����;
	� �������������� ����� Notify � �������� �� ���� ������� SendEmail.

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
