/*
Функция int GetDistinctRealRootCount(double a, double b, double c);
возвращает количество уникальных действительных корней уравнения
ax² + bx + c = 0. Разработайте набор юнит-тестов для проверки
корректности реализации этой функции. Случай, когда все три
коэффициента равны нулю, тестировать не надо.

Начать работу вы можете с шаблона, который содержит наш фреймворк
юнит-тест и заготовку функции GetDistinctRealRootCount.
*/

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
	int result = 0;
	if (a == 0) {        // If equation is linear
		if (b == 0) {
			result = 0;
		} else {
			result = 1;
		}
	} else {             //  If equation is square
		int D = b*b - 4*a*c;
		if (D > 0) {
			result = 2;
		} else if (D == 0) {
			result = 1;
		} else {
			result = 0;
		}
	}
	return result;
}

void TestLinearEq() {
	AssertEqual(GetDistinctRealRootCount(0, 2, 1), 1, "2x + 1 = 0");
	AssertEqual(GetDistinctRealRootCount(0, -1, 0), 1, "-x = 0");
	AssertEqual(GetDistinctRealRootCount(0, 120, -10), 1, "120x -10 = 0");
}

void TestConstant() {
	AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0,
			"c = 0, where c = 1 has 0 real roots");
	AssertEqual(GetDistinctRealRootCount(0, 0, -10), 0,
			"c = -10, where c = -10 has 0 real roots");
	AssertEqual(GetDistinctRealRootCount(0, 0, 189238910), 0,
		"c = 0, where c = 189238910 has 0 real roots");
}

void TestTwoRoot() {
	AssertEqual(GetDistinctRealRootCount(3, 10, 5), 2, "3x^2 + 10x + 5 = 0");
	AssertEqual(GetDistinctRealRootCount(-5, 4, 2), 2, "-5x^2 - 4x + 2 = 0");
	AssertEqual(GetDistinctRealRootCount(4, 0, -16), 2, "4x^2 - 16 = 0");
}

void TestOneRoot() {
	AssertEqual(GetDistinctRealRootCount(1, 2, 1), 1, "x^2 + 2x + 1 = 0");
	AssertEqual(GetDistinctRealRootCount(1, -2, 1), 1, "x^2 -2x + 1 = 0");
}

void TestNoRoot() {
	AssertEqual(GetDistinctRealRootCount(2, 1, 5), 0, "2x^2 + x + 5 = 0");
	AssertEqual(GetDistinctRealRootCount(-2, 1, -5), 0, "-2x + x - 5 = 0");
	AssertEqual(GetDistinctRealRootCount(4, 0, 16), 0, "4x^2 + 16 = 0");

}

void TestRootCount() {
	mt19937 gen;
	uniform_real_distribution<> unif(-10, 10);

	for (auto i = 0; i < 100; ++i) {
		const auto a = unif(gen);
		const auto b = unif(gen);
		const auto c = unif(gen);

		const auto count = GetDistinctRealRootCount(a, b, c);

		Assert(count >= 0 && count <= 2, "Quadratic equation has "
				"only 0, 1, 2 real roots");
	}
}

int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
  runner.RunTest(TestLinearEq, "TestLinearEq");
  runner.RunTest(TestConstant, "TestConstant");
  runner.RunTest(TestTwoRoot, "TestTwoRoot");
  runner.RunTest(TestOneRoot, "TestOneRoot");
  runner.RunTest(TestNoRoot, "TestNoRoot");
  runner.RunTest(TestRootCount, "TestRootCount");
  return 0;
}

