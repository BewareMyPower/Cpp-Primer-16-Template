// print_type.cc
#include <iostream>
#include <string>
#include <type_traits>
#include "array1d.h"
#include "pointer.h"
using namespace std;

template <typename T>
void f1(T, T) {
  Pointer<T>("f1() T").print();
  cout << "--------------" << endl;
}

template <typename T1, typename T2>
void f2(T1, T2) {
  Pointer<T1>("f2() T1").print();
  Pointer<T2>("f2() T2").print();
  cout << "--------------" << endl;
}

int main() {
  base_type_test();
  cout << "--------------" << endl;
  pointer_test();
  cout << "--------------" << endl;
  array1d_test();
  cout << "--------------" << endl;
  int i = 0, j = 42, *p1 = &i, *p2 = &j;
  const int *cp1 = &i, *cp2 = &j;
  f1(p1, p2);
  f2(p1, p2);
  f1(cp1, cp2);
  f2(cp1, cp2);
  //  f1(p1, cp1);
  f2(p1, cp1);
  return 0;
}
