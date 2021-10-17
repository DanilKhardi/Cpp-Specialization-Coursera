#include <iostream>
#include <string>
using namespace std;

int main() {
	string word;
	cin >> word;
	int cnt = 0;
	for (int i = 0; i < word.size(); ++i) {
	if (word[i] == 'f') {
		++cnt;
		if (cnt == 2) {
			cout << i;
			break;
	}

		}
	}
	if (cnt == 1) {
		cout << -1;
	}
	else if (cnt == 0) {
		cout << -2;
	}
	return 0;
}
