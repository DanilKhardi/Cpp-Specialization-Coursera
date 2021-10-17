#include <iostream>
using namespace std;

int main() {
	int A, B;
	cin >> A >> B;
	if (B == 0) {
		cout << "Impossible";
	} else if (A < B) {
		cout << 0;
	} else {
		cout << A / B;
	}
	return 0;
}
