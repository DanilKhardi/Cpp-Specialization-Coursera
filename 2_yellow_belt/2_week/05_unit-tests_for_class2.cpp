/*
Разработайте набор юнит-тестов, которые будут проверять корректность
реализации класса Rational. Тестировать случай, когда знаменатель равен
нулю, не надо.

Список требований, предъявляемых к реализации интерфейса класса Rational:

	► Конструктор по умолчанию должен создавать дробь с числителем 0 и
	знаменателем 1.

	► При конструировании объекта класса Rational с параметрами p и q
	должно выполняться сокращение дроби p/q.

	► Если дробь p/q отрицательная, то объект Rational(p, q) должен
	иметь отрицательный числитель и положительный знаменатель.

	► Если дробь p/q положительная, то объект Rational(p, q) должен иметь
	положительные числитель и знаменатель (обратите внимание на случай
	Rational(-2, -3)).

	► Если числитель дроби равен нулю, то знаменатель должен быть равен 1.

*/

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>

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

template<class X>
ostream& operator << (ostream& os, const pair<X, X>& p) {
	os << "(" << p.first << ", "  << p.second << ")";
	return os;
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

class Rational {
public:
  // Вы можете вставлять сюда различные реализации,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный

  Rational() {
	  numerator_ = 0;
	  denominator_ = 1;
  }
  Rational(int numerator, int denominator) {
	  int common_div = gcd(numerator, denominator);
	  numerator_ = numerator / common_div;
	  denominator_ = denominator / common_div;
	  if (denominator_ < 0) {
		  numerator_ = -numerator_;
		  denominator_ = -denominator_;
	  }
  }

  int Numerator() const {
	  return numerator_;
  }

  int Denominator() const {
	  return denominator_;
  }
private:
  int numerator_;
  int denominator_;
};

void AssertRational(const Rational& r, const pair<int, int>& correct,
		const string& message) {
	AssertEqual(pair<int, int>(r.Numerator(), r.Denominator()), correct, message);
}

const auto p = [](int numerator, int denominator) {
	return pair<int, int>(numerator, denominator);
};


void TestRational() {

	AssertRational(Rational(3, 10), p(3, 10), "test1");
	AssertRational(Rational(8, 12), p(2, 3), "test2");
	AssertRational(Rational(-4, 6), p(-2, 3), "test3");
	AssertRational(Rational(0, 15), p(0, 1), "test4");
	AssertRational(Rational(), p(0, 1), "test5");
	AssertRational(Rational(-2, -3), p(2, 3), "test6");

}


int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
  runner.RunTest(TestRational, "TestRational");
  return 0;
}
