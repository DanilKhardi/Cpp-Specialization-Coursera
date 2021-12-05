/*
Модифицируйте решение предыдущей части так, чтобы предыдущее выражение обрамлялось
скобками лишь при необходимости, то есть только в том случае, когда очередная
операция имеет бо́льший приоритет, чем предыдущая.
*/

#include <iostream>
#include <string>
#include <deque>
using namespace std;


int main() {
	string result, operation = "";
	int x, N, y;
	cin >> x >> N;
	deque<string> expression(N);
	expression.push_front(to_string(x));
	for (int i = 0; i < N; ++i) {
		string prev_operation = operation;
		cin >> operation >> y;
		if (operation == "+" or operation == "-") {
			expression.push_back(" ");
			expression.push_back(operation);
			expression.push_back(" ");
			expression.push_back(to_string(y));
		} else {
			if (prev_operation == "+" or prev_operation == "-") {
				expression.push_front("(");
				expression.push_back(")");
				expression.push_back(" ");
				expression.push_back(operation);
				expression.push_back(" ");
				expression.push_back(to_string(y));

			} else {
				expression.push_back(" ");
				expression.push_back(operation);
				expression.push_back(" ");
				expression.push_back(to_string(y));
			}
		}
	}
	for (auto i : expression) {
		cout << i;
	}
	return 0;
}
