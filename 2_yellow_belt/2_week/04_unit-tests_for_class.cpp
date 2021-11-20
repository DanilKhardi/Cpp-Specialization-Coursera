/*
В первом курсе «Белый пояс по С++» у нас была задача «Имена и фамилии — 1».
В ней надо было разработать класс Person, поддерживающий историю изменений
человеком своих фамилии и имени. В данной задаче вам надо разработать
юнит-тесты на реализацию класса Person. При разработке тестов учитывайте
ограничения, которые накладывает на класс Person условие задачи «Имена и
фамилии — 1».
*/

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

struct PersonInfo {
	string name = "";
	string surname = "";
};

class Person {
public:
  // Вы можете вставлять сюда различные реализации класса,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  void ChangeFirstName(int year, const string& first_name) {
	  storage_history_[year].name = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
	  storage_history_[year].surname = last_name;
  }
  string GetFullName(int year) {
	  for (const auto& i : storage_history_) {
		  if (i.first > year) return "Incognito";
		  break;
	  }
	  if (storage_history_.empty()) return "Incognito";
	  else {
		  string name = "";
		  string surname = "";
		  for (const auto& i : storage_history_) {
			  if (i.first <= year && i.second.name != "") name = i.second.name;
			  if (i.first <= year && i.second.surname != "") surname = i.second.surname;
		  }
		  if (name == "") return surname + " with unknown first name";
		  else if (surname == "") return name + " with unknown last name";
		  else return name + " " + surname;
	  }
  }
private:
  map<int, PersonInfo> storage_history_;
};

void TestExistNameSurname() {
	Person p;
	p.ChangeFirstName(1900, "Olga");
	p.ChangeLastName(1901, "Petrova");

	AssertEqual(p.GetFullName(1901), "Olga Petrova", "test_1");

	p.ChangeFirstName(1905, "Ekaterina");
	p.ChangeLastName(1907, "Velikaya");

	AssertEqual(p.GetFullName(1904), "Olga Petrova", "test_2");
	AssertEqual(p.GetFullName(1905), "Ekaterina Petrova", "test_3");
	AssertEqual(p.GetFullName(1907), "Ekaterina Velikaya", "test_4");

}

void TestExistName() {
	Person p;
	p.ChangeFirstName(1900, "Olga");

	AssertEqual(p.GetFullName(1905), "Olga with unknown last name", "test_5");

	p.ChangeFirstName(1910, "Ekaterina");

	AssertEqual(p.GetFullName(1910), "Ekaterina with unknown last name", "test_6");
	AssertEqual(p.GetFullName(1909), "Olga with unknown last name", "test_7");

}

void TestExistSurname() {
	Person p;
	p.ChangeLastName(1900, "Petrova");

	AssertEqual(p.GetFullName(1900), "Petrova with unknown first name", "test_8");

	p.ChangeLastName(1910, "Velikaya");
	AssertEqual(p.GetFullName(1905), "Petrova with unknown first name", "test_9");
	AssertEqual(p.GetFullName(1911), "Velikaya with unknown first name", "test_10");
}

void TestIncognito() {
	Person p;
	AssertEqual(p.GetFullName(1910), "Incognito", "test_11");

	p.ChangeFirstName(1910, "Olga");
	p.ChangeLastName(1910, "Petrova");

	AssertEqual(p.GetFullName(1909), "Incognito", "test_12");
}

int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
  runner.RunTest(TestExistNameSurname, "TestExistNameSurname");
  runner.RunTest(TestExistName, "TestExistName");
  runner.RunTest(TestExistSurname, "TestExistSurname");
  runner.RunTest(TestIncognito, "TestIncognito");

  return 0;
}
