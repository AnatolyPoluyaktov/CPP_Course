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
    Rational() {
        num = 0;
        denum = 1;
    }

    Rational(int numerator, int denominator) {
        if (denominator == 0){
            throw invalid_argument("invalid_argument");
        }
        if (numerator == 0){
            num = 0;
            denum = 1;
        }
        else  if(gcd(numerator,denominator) == 1){
            num = numerator;
            denum = denominator;
        }
        else {
            int div = gcd(numerator,denominator);
            num = numerator/div;
            denum = denominator/div;



        }
        if (num <0 && denum < 0){
            num=abs(num);
            denum = abs(denum);
        }
        else if(num > 0 && denum <0){
            num *=-1;
            denum *=(-1);
        }
    }



    int Numerator() const {
        return num;
    }

    int Denominator() const {
        return denum;
    }
    // bool operator==(const Rational& l){
    //   return (l.num ==this->num && l.denum == this->denum);
    //}
    int num;
    int denum;
private:

};
bool operator==(const Rational& l , const Rational& r){
    return (l.num == r.num && l.denum == r.denum);
}
bool operator!=(const Rational& l , const Rational& r){
    return !(l.num == r.num && l.denum == r.denum);
}
Rational operator+( const Rational& l ,const  Rational& r){
    return Rational(l.num*r.denum + r.num*l.denum , l.denum *r.denum);
}
Rational operator-( const Rational& l ,const  Rational& r){
    return Rational(l.num*r.denum - r.num*l.denum , l.denum *r.denum);
}
Rational operator*( const Rational& l ,const  Rational& r){
    return  Rational(l.num*r.num, l.denum * r.denum);
}
Rational operator/( const Rational& l ,const  Rational& r){
    if(r.num == 0){
        throw domain_error("Division by zero");
    }
    return  Rational(l.num*r.denum, l.denum * r.num);
}
istream& operator>>(istream& stream ,  Rational& ratio){
    int n, d;
    char c;
    stream >> n >> c >> d;

    if (stream && c == '/') {
        ratio = Rational(n, d);
    }
    else {
        throw invalid_argument("Invalid argument");
    }
    return stream;

}
ostream& operator<<(ostream& stream , const Rational& ratio){
    stream << ratio.num << '/' << ratio.denum;
    return stream;
}
bool operator <( const Rational& l , const Rational& r){
    if(l.denum == r.denum)
        return (r.num <l.num);
    return((l.num*r.denum)<(r.num*l.denum));
}

void TestCorrection()
{
   Rational frac1;
   AssertEqual(frac1.Numerator(),0, "numerator 0");
   AssertEqual(frac1.Denominator(),1, "denumerator 1");
   Rational frac2{2,4};
   AssertEqual(frac2.Numerator(),1, "2/4= 1/2");
    AssertEqual(frac2.Denominator(),2, "2/4= 1/2");
    frac2 = Rational{182,195};
    AssertEqual(frac2.Numerator(),14, "182/195= 1/2");
    AssertEqual(frac2.Denominator(),15, "182/195= 1/2");
   frac1 = Rational{3,-4};
   AssertEqual(frac1.Numerator(), -3, " 3/-4 == -3/4");
   AssertEqual(frac1.Denominator(), 4, " 3/-4 == -3/4");

    frac1 = Rational{-3,-4};
    AssertEqual(frac1.Numerator(), 3, " -3/-4 == 3/4");
    AssertEqual(frac1.Denominator(), 4, " -3/-4 == 3/4");

    frac1 = Rational{0,4};
    AssertEqual(frac1.Numerator(), 0, " 0/4 == 0/1");
    AssertEqual(frac1.Denominator(), 1, " 0/4 == 0/1");

     frac1 = Rational{numeric_limits<int>::max(), 4 } ;
    AssertEqual( frac1.Numerator(),numeric_limits<int>::max(), "bug nums");
    AssertEqual(frac1.Denominator(),4, "big nums");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestCorrection, "test correction");
    return 0;
}
