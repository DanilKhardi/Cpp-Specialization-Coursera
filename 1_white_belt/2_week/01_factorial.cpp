/*
 * Напишите функцию, которая называется Factorial возвращает int
принимает int и возвращает факториал своего аргумента. Гарантируется,
что аргумент функции по модулю не превышает 10. Для отрицательных
аргументов функция должна возвращать 1.
 */


#include <iostream>
using namespace std;

int Factorial(int x) {
	int result = 1;
	if (x <= 1) {
		return result;
	}
	else {
		for (int i = 1; i <= x; ++i) {
			result *= i;

		}
	} return result;
}

