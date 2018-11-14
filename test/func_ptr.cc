// func_ptr.cc
#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

template <typename T>
int compare(const T& lhs, const T& rhs) {
  if (lhs < rhs) return -1;
  if (rhs < lhs) return 1;
  return 0;
}

template <typename T>
void f(T& x) {
  if (is_pointer<T>::value) {
    cout << "T is pointer" << endl;
  }
}

int main() {
  int (*compare_int)(const int&, const int&) = compare<int>;
  cout << compare_int(1, 1) << endl;
  auto compare_string = compare<string>;
  cout << compare_string("hello", "world") << endl;

  // T被推断为函数指针
  f(compare_int);
  f(compare_string);
}
