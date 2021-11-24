/*
Вам дан заголовочный файл phone_number.h, содержащий объявление класса PhoneNumber.
При этом в комментариях описано поведение, которое ожидается от реализации этого класса.
*/


#include <iostream>
#include <sstream>
#include <exception>

#include "phone_number.h"

using namespace std;

// Class Implementation

PhoneNumber::PhoneNumber(const string& international_number) {
	istringstream is(international_number);

	char sign = is.get();
	getline(is, country_code_, '-');
	getline(is, city_code_, '-');
	getline(is, local_number_);

	if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
		throw invalid_argument("Phone number has incorrect format");
	}
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
}

int main() {
	// testing code

	PhoneNumber pn("+7-1233");
	cout << pn.GetCountryCode() << endl;
	cout << pn.GetCityCode() << endl;
	cout << pn.GetLocalNumber() << endl;
	cout << pn.GetInternationalNumber();
	return 0;
}
