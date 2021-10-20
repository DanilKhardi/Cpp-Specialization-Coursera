/*
Напишите функцию, которая называется PalindromFilter
возвращает vector<string> принимает vector<string> words
и int minLength и возвращает все строки из вектора words,
которые являются палиндромами и имеют длину не меньше minLength
*/

#include <iostream>
#include <vector>
#include<string>
using namespace std;

bool IsPalindrom(string s) {
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

vector<string> PalindromFilter(vector<string> words, int minLength) {
	vector<string> result;
	for (string word: words) {
		if (IsPalindrom(word) && word.size() >= minLength) {
			result.push_back(word);
		}
	}
	return result;
}
