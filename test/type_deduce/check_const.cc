// check_const.cc
#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
void check_const() {
  if (is_const<T>::value)
    cout << "const" << endl;
  else
    cout << "non-const" << endl;
}

template <typename T>
void f1(T&) {
  check_const<T>();
}

template <typename T>
void f2(const T&) {
  check_const<T>();
}

template <typename T>
void f3(T&&) {
  check_const<T>();
}

int main() {
  int i = 1;
  const int ci = 2;
  int& ri = i;
  const int& rci = i;
  cout << "f(T&)..." << endl;
  f1(i);
  f1(ci);  // T is const int
  f1(ri);
  f1(rci);  // T is const int
  cout << "f(const T&)..." << endl;
  // T均被推断为int
  f2(i);
  f2(ci);
  f2(ri);
  f2(rci);
  f2(5);  // const T&可以绑定右值
  cout << "f(T&&)..." << endl;
  // T均被推断为int
  f3(i);
  f3(ci);
  f3(ri);
  f3(rci);
  f3(5);
  return 0;
}
