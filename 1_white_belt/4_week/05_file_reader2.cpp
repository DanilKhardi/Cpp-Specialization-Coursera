/*
В этом задании вам предстоит написать две небольшие программы.
Каждый пункт - отдельная задача, решение отправляйте в поле с
соответствующим номером.

Часть 2
Снова считайте все содержимое файла input.txt, но на этот раз
выведите его в файл output.txt . Точно так же гарантируется,
что содержимое файла input.txt заканчивается переводом строки.

Пример
input.txt

Keep calm
and
learn C++

output.txt
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
		ofstream output("output.txt");
		while (getline(input, line)){
			output << line << endl;
		}
	}
}
