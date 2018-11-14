// check_reference.cc
#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
void check_reference() {
  if (is_lvalue_reference<T>::value) cout << "T is &" << endl;
  if (is_rvalue_reference<T>::value) cout << "T is &&" << endl;
  if (!is_reference<T>::value) cout << "T is not reference" << endl;
}

// 引用折叠只能应用于间接创建的引用的引用，如类型别名或模板参数
// T& &、T& &&、T&& & => T&
// T&& && => T&&
// 因此可以将任意类型的实参传递给T&&
template <typename T>
void f(T&&) {
  // 1. 传入int&&，匹配成T=int
  // 2. 传入int&，匹配成T=int&
  // 3. 传入int，根据传入的变量是否左值判断是int&还是int&&
  check_reference<T>();
}

int main() {
  int i = 1;
  const int ci = 2;
  int& ri = i;
  const int& rci = i;

  // 左值引用，&
  f(ri);
  f(rci);
  // 非临时变量(左值)，&
  f(i);
  f(ci);
  // 临时变量(右值)，not reference
  f(5);
  // 右值引用，not reference
  f(std::move(i));
}
