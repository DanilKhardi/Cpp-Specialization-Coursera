/*
 * Напишите функцию, которая называется IsPalindrom возвращает bool
принимает параметр типа string и возвращает, является ли переданная
строка палиндромом
Палиндром - это слово или фраза, которые одинаково читаются слева
 направо и справа налево. Пустая строка является палиндромом.
 */

#include <iostream>
#include <string>
using namespace std;

bool IsPalindrom(string s) {
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}
