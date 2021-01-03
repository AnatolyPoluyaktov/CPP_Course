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


class Person {
public:
    // Вы можете вставлять сюда различные реализации класса,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
    void ChangeFirstName(int year, const string& first_name) {
         fname[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        lname[year] = last_name;
    }
     string GetName(int year)
     {
        string name = "";
        for(auto [key, value] : fname)
        {
            if (key <= year)
                name = value;
        }

        return name;
     }
    string GetLastName(int year)
    {
        string last_name = "";
        for(auto [key, value] : lname)
        {
            if (key <= year)
                last_name = value;
        }

        return last_name;
    }
    string GetFullName(int year) {
        string name = GetName(year);
        string last_name = GetLastName(year);
         if ( name.empty() && last_name.empty())
             return "Incognito";
         else if  (name.empty() && !last_name.empty())
             return last_name + " with unknown first name";
         else if  (!name.empty() && last_name.empty())
             return name + " with unknown last name";
         else
             return name + " " + last_name;
    }
private:
    map<int, string>fname;
    map<int, string >lname;
};

void TestGetFullName() {
    Person person;
    AssertEqual(person.GetFullName(1900), "Incognito", "empty");
    person.ChangeFirstName(1910, "Polina");
    AssertEqual(person.GetFullName(1905), "Incognito", "it must empty");
    AssertEqual(person.GetFullName(1990), "Polina with unknown last name", "only name");
    AssertEqual(person.GetFullName(1910), "Polina with unknown last name", "only name");
    person.ChangeLastName(1910, "Sergeeva");
    AssertEqual(person.GetFullName(1905), "Incognito", "it must be empty");
    AssertEqual(person.GetFullName(1910), "Polina Sergeeva", "fullname");
    AssertEqual(person.GetFullName(1920), "Polina Sergeeva", "fullname");

    Person person2;
    person2.ChangeLastName(2000, "Miller");
    AssertEqual(person2.GetFullName(1990), "Incognito", "empty");
    AssertEqual(person2.GetFullName(2010), "Miller with unknown first name", "only last name");
}

    int main() {
    TestRunner runner;
    runner.RunTest(TestGetFullName, "GetFullName");
    Person person;
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }
    return 0;
}
