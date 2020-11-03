#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include<cmath>
using namespace std;



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

int CalcD(int a, int b, int c)
{
   int D = b * b - 4 * a * c;
   if (D > 0)
       return 2;
   if (D < 0)
       return 0;
   return 1;
}
int QuadricEq(int a, int b, int c)
{
    if (a != 0 && b != 0 & c != 0) //1
       return CalcD(a, b , c);

    if (a != 0 && b != 0 & c == 0) //2
        return 2;

    if (a !=0 && b == 0 && c != 0) //3
    {
        if ( a < 0 && c > 0)
            return 2;
        if ( a > 0 && c < 0)
            return 2;
        if (a > 0 && c > 0)
            return 0;
    }

    return  1;//4
}

int LinearEq(int b, int c)
{
    if ( b != 0 && c != 0) //1
        return 1;

    if ( b !=0 && c == 0) //2
        return 1;

    return 0;//3
}



int GetDistinctRealRootCount(double a, double b, double c) {
  if (a !=0)
      return QuadricEq(a, b, c);
  return LinearEq(b, c);
}
void TestQuadtic()
{   //1
    AssertEqual(GetDistinctRealRootCount(-2, 2, 2), 2,"a != 0, b !=0, c !=0, D > 0");
    AssertEqual(GetDistinctRealRootCount(2, 2, 2), 0,"a != 0, b !=0, c !=0, D < 0");
    AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1,"a != 0, b !=0, c !=0, D == 0");

    //2
    AssertEqual(GetDistinctRealRootCount(-2, 2, 0), 2,"a != 0, b !=0, c == 0");

    //3
    AssertEqual(GetDistinctRealRootCount(-2, 0, 2), 2,"a < 0, b == 0, c > 0");
    AssertEqual(GetDistinctRealRootCount(2, 0, -2), 2,"a > 0, b == 0, c < 0");
    AssertEqual(GetDistinctRealRootCount(2, 0, 2), 0,"a > 0, b == 0, c !=0");

    //4
    AssertEqual(GetDistinctRealRootCount(2, 0, 0), 1,"a !=0 0, b == 0, c == 0");

}
void TestLinear()
{   //1
    AssertEqual(GetDistinctRealRootCount(0, 2, 2), 1 , " a == 0, b!=0 , c!=0");

    //2
    AssertEqual(GetDistinctRealRootCount(0, 2, 0), 1 , " a == 0, b!=0 , c == 0");

    //3
    AssertEqual(GetDistinctRealRootCount(0, 0, 2), 0 , " a == 0, b == 0 , c !=0");
}
int main() {
  TestRunner runner;
  runner.RunTest(TestQuadtic,"Test quadtic equetion");
  runner.RunTest(TestLinear,"Test Linear equetion");

  return 0;
}
