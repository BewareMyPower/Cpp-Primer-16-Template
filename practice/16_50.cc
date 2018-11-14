// 16_50.cc
#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
inline void printType(const char* name) {
  cout << name << " is ";
  if (is_pointer<T>::value) {
    using value_type = typename remove_pointer<T>::type;
    if (is_const<value_type>::value) cout << "const ";
    cout << "int*";
    if (is_const<T>::value) cout << " const";
    cout << endl;
  } else {
    if (is_const<T>::value) cout << "const ";
    cout << "int" << endl;
  }
}

template <typename T>
void f(T t) {
  cout << "# f<T>(T arg)" << endl;
  printType<T>("T");
  printType<decltype(t)>("arg");
}

template <typename T>
void f(const T* t) {
  cout << "# f<T>(const T* arg)" << endl;
  printType<T>("T");
  printType<decltype(t)>("arg");
}

template <typename T>
void g(T t) {
  cout << "# g<T>(T arg)" << endl;
  printType<T>("T");
  printType<decltype(t)>("arg");
}

template <typename T>
void g(T* t) {
  cout << "# g<T>(T* arg)" << endl;
  printType<T>("T");
  printType<decltype(t)>("arg");
}

int main() {
  int i = 42, *p = &i;
  const int ci = 0, *p2 = &ci;
#define TEST(func) \
  func(42);        \
  func(p);         \
  func(ci);        \
  func(p2);
  TEST(g);
  TEST(f);
#undef TEST
  return 0;
}
