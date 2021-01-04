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

 bool checkEven(const string& str)
 {
     if (str.empty())
         return true;
     size_t len = str.size();
     for(size_t i =0 ,  j = len-1 ; (i < (len/2)+1) && (j > (len/2)-1); ++i, --j ){
         if (str[i] != str[j])
             return false;
     }
     return true;
 }

 bool checkOdd(const string& str)
 {
     if (str.size() == 1)
         return true;
     size_t len = str.size();
     for(size_t i =0 ,  j = len-1 ; (i < (len/2)) && (j > (len/2)); ++i, --j ){
         if (str[i] != str[j])
             return false;
     }
     return true;
 }

bool IsPalindrom(const string& str) {
     if ( str.size()% 2)
         checkOdd(str);
     else
         checkEven(str);
}
void TestPalindrom()
{    Assert(IsPalindrom(""), "Is  palindrome");
    Assert(IsPalindrom(" "), "Is  palindrome");
    Assert(IsPalindrom("lool"), "Is  palindrome");
    Assert(IsPalindrom("o"), "Is  palindrome");
    Assert(IsPalindrom("1"), "Is  palindrome");
    Assert(!IsPalindrom("madaM"), "Not a palindrome");
    Assert(!IsPalindrom("leveL"), "Not a palindrome");
    Assert(!IsPalindrom("Level"), "Not a palindrome");
    Assert(!IsPalindrom("level "), "Not a palindrome");
    Assert(!IsPalindrom(" llevell"), "Not a palindrome");
    Assert(IsPalindrom("top pot"), " is palindrome");
    Assert(IsPalindrom("l e v e l"), "Is palindrome");
    Assert(IsPalindrom("l  e  v  e  l"), "Is palindrome");
    Assert(!IsPalindrom(" lev e  l   "), "Is not palindrome");
    Assert(!IsPalindrom("mada m"), "Is not palindrome");
    Assert(!IsPalindrom("   madam  "), "Is not palindrome");
    Assert(IsPalindrom("MADAM"), "Is  palindrome");
    Assert(IsPalindrom("o lol o"), "Is  palindrome");
    Assert(!IsPalindrom(" madam"), "Is not palindrome");
    Assert(!IsPalindrom(" madrydam"), "Is not palindrome");
    Assert(IsPalindrom("wasitacaroracatisaw"), "Is  palindrome");
    Assert(IsPalindrom("   tutneotmfmtoentut   "), "Is  palindrome");
    Assert(!IsPalindrom("__lool___"), "is not palindrome");
    Assert(IsPalindrom("        a        "),"Is palindrome");
    Assert(IsPalindrom("      "),"Is palindrome");
    Assert(IsPalindrom("     "),"Is palindrome");
    Assert(!IsPalindrom("     qq"),"Is not palindrome");
    Assert(!IsPalindrom("  q q "),"Is not palindrome");
    Assert(
            !IsPalindrom("was it a car or a cat i saw"),
            "`was it a car or a cat i saw` is not a palindrome because spaces do not match"
    );
    Assert(!IsPalindrom("ABBA   "), "ABBA   is not a palindrome");
    Assert(!IsPalindrom("  ABBA"), "  ABBA is not a palindrome");
    Assert(!IsPalindrom("XabbaY"), "XabbaY is not a palindrome");
    Assert(!IsPalindrom("abXYba"), "abXYba is not a palindrome");
    Assert(!IsPalindrom("Xabba"), "Xabba is not a palindrome");
    Assert(!IsPalindrom("abbaX"), "abbaX is not a palindrome");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestPalindrom,"test pandrom");

    return 0;
}
