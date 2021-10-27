/*
В этом задании вам предстоит написать две небольшие программы.
Каждый пункт - отдельная задача, решение отправляйте в поле с
соответствующим номером.

Часть 1
Ваша программа должна считать содержимое файла input.txt и
напечатать его на экран без изменений. Гарантируется, что
содержимое файла input.txt заканчивается переводом строки.

Пример
input.txt

Keep calm
and
learn C++

stdout
Keep calm
and
learn C++
*/


#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main() {
	ifstream input("input.txt");
	if (input.is_open()){
		string line;
		while (getline(input, line)){
			cout << line << '\n';
		}
	}
}
