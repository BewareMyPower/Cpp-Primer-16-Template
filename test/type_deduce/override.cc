// override.cc
#include <iostream>
using namespace std;

template <typename T>
void f(T&) {
  cout << "T&" << endl;
}

template <typename T>
void f(const T&) {
  cout << "const T&" << endl;
}

template <typename T>
void f(T&&) {
  cout << "T&&" << endl;
}

int main() {
  int i = 1;
  const int ci = 2;
  int& ri = i;
  const int& rci = i;
  f(i);  // T&, T&&, const T&
  f(ci);  // const T&
  f(ri);  // T&, T&&, const T&
  f(rci); // const T&
  return 0;
}
