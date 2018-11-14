// 16_42.cc
#include <iostream>
#include "const_reference.h"
using namespace std;

template <typename T>
void g(T&& val) {
  cout << "T is ";
  ConstReference<T>().print();
  cout << "val is ";
  ConstReference<decltype(val)>().print();
}

int main() {
  int i = 0;
  const int ci = i;
  g(i);
  g(ci);
  g(i * ci);
  g(i = ci);
}
