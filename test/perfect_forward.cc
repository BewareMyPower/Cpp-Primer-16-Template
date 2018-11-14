// perfect_forward.cc
#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
void printType();

template <typename T>
void f(T&& t) {
  printType<decltype(t)>();
}

template <typename T>
void g1(T&& t) {
  // 直接转发参数，如果实参是右值，那么转发的t是左值
  f(t);
}

template <typename T>
void g2(T&& t) {
  f(static_cast<T&&>(t));
}

template <typename T>
void g3(T&& t) {
  f(static_cast<decltype(t)>(t));
}

int main() {
  int i = 0;
  int& ri = i;
#define TEST(f) \
  f(i);         \
  f(ri);        \
  f(5)
  cout << ">> f(i)" << endl;
  TEST(f);  // T&; T&; T&&
  cout << ">> g1(i) = f(t)" << endl;
  TEST(g1);  // T&; T&; T&
  cout << ">> g2(i) = f(static_cast<T&&>(t))" << endl;
  TEST(g2);  // T&; T&; T&&
  cout << ">> g3(i) = f(static_cast<decltype(t)>(t))" << endl;
  TEST(g3);  // T&; T&; T&&
#undef TEST
  // https://stackoverflow.com/questions/25133904/why-do-we-need-second-stdforward-specialization
  // 为什么需要第二种重载方式？
  // 比如T=int，forward(int&)无法接受一个右值做参数，右值无法转发成左值引用，因此验证了
  // 参数是否为左值引用(采用static_assert)
  // T=int&，remove_reference<T>&&=int&&，匹配forward重载2
  // 而将右值转发成左值引用时不安全的，触发static_assert
  // std::forward<int&>(1);  // 编译错误
}

template <typename T>
void printType() {
  if (is_reference<T>::value) {
    using value_type = typename remove_reference<T>::type;
    if (is_const<value_type>::value) cout << "const ";
    cout << "T&";
    if (is_rvalue_reference<T>::value) cout << "&";
    cout << endl;
  } else {
    if (is_const<T>::value) cout << "const ";
    cout << "T" << endl;
  }
}
