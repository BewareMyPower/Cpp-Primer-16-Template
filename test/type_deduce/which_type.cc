// which_type.cc
#include <iostream>
using namespace std;

template <typename T>
void f(T&& val) {
  // T可能是引用，也可能不是
  cout << "val = " << val << endl;
  T t = val;
  t = 100;
  cout << "t = " << t << endl;
  cout << "val = " << val << endl;
}

int main() {
  int i = 0;
  f(i);  // T被推断为int&
  cout << i << endl;

  int j = 0;
  f(std::move(j));  // T被推断为int
  cout << j << endl;
}
