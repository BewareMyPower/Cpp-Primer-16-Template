// pointer.h
#pragma once
#include <iostream>
#include "base_type.h"

template <typename T>
struct Pointer {
  using value_type = typename std::remove_pointer<T>::type;

  // FIXME: 未判断指针指向的类型是否为基本类型
  static constexpr bool isValid() noexcept { return std::is_pointer<T>::value; }

  Pointer(const std::string& name) : name_(name) {}

  void print(std::ostream& os = std::cout) {
    using std::endl;
    os << name_ << " is ";
    if (isValid()) {
      if (std::is_const<value_type>::value) os << "const ";
      os << BaseType<value_type>::toString() << "*";
      if (std::is_const<T>::value) os << " const";
      os << endl;
    } else {
      os << "not pointer" << endl;
    }
  }

  std::string name_;
};

// unit test
inline void pointer_test() {
  int i = 0;
  const int* p1 = &i;
  int* p2 = &i;
  int* const p3 = &i;
  const int* const p4 = &i;
  double a[15];
  const double ca[] = {1.0, 2.0, 3.0, 4.0, 5.0};

#define PRINT_TYPE(x, s) Pointer<decltype(x)>(s).print();
  PRINT_TYPE(i, "i");
  PRINT_TYPE(p1, "p1");
  PRINT_TYPE(p2, "p2");
  PRINT_TYPE(p3, "p3");
  PRINT_TYPE(p4, "p4");
  PRINT_TYPE(a, "a");
  PRINT_TYPE(ca, "ca");
#undef PRINT_TYPE
}
