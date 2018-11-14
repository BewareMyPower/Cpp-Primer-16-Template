// const_reference.h
#pragma once
#include <iostream>
#include <type_traits>

template <typename T>
struct ConstReference {
  void print() {
    using std::cout;
    using std::endl;

    if (std::is_reference<T>::value) {
      using value_type = typename std::remove_reference<T>::type;

      if (std::is_const<value_type>::value) cout << "const ";
      if (std::is_lvalue_reference<T>::value)
        cout << "T&" << endl;
      else
        cout << "T&&" << endl;
    } else {
      if (std::is_const<T>::value) cout << "const ";
      cout << "T" << endl;
    }
  }
};

inline void const_reference_test() {
  int i = 0;
  int& ri = i;
  const int ci = i;
  const int& rci = i;
  ConstReference<decltype(i)>().print();
  ConstReference<decltype(ri)>().print();
  ConstReference<decltype(ci)>().print();
  ConstReference<decltype(rci)>().print();
}
