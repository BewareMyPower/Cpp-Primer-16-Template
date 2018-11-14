// test.cc
#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
using remove_reference_t = typename std::remove_reference<T>::type;

template <typename T>
void f(remove_reference_t<T>& x) {
  //cout << "f(T&)" << endl;
}

template <typename T>
void f(remove_reference_t<T>&& x) {
  //cout << "f(T&&)" << endl;
}

template <typename T>
void g(T&& t) {
  if (is_lvalue_reference<T>::value) cout << "g(int&)" << endl;
  if (is_rvalue_reference<T>::value) cout << "g(int&&)" << endl;
  if (!is_reference<T>::value) cout << "g(int)" << endl;
  f<T>(t);
}

int main() {
  int i = 0;
  int& ri = i;
  g(i);
  g(ri);
  // 实参int&&，推断T为int&&
  g(std::move(i));
  g(3);
}
