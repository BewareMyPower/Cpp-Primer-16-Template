// array1d.h
#pragma once
#include <iostream>
#include "base_type.h"

template <typename T>
struct Array1d {
  using value_type = typename std::remove_extent<T>::type;

  static constexpr bool isValid() noexcept {
    return std::is_array<T>::value && std::extent<T, 1>::value == 0;
  }

  Array1d(const std::string& name) : name_(name) {}

  void print(std::ostream& os = std::cout) {
    using std::endl;
    os << name_ << " is ";
    if (isValid()) {
      if (std::is_const<value_type>::value) os << "const ";
      os << BaseType<value_type>::toString();
      os << "[" << std::extent<T, 0>::value << "]" << endl;
    } else {
      os << "not 1D array" << endl;
    }
  }

  std::string name_;
};

// unit test
inline void array1d_test() {
  int a[13], aa[10][12];
  const int ca[] = {4, 5, 6, 8};

#define PRINT_TYPE(x, s) Array1d<decltype(x)>(s).print();
  PRINT_TYPE(a, "a");
  PRINT_TYPE(ca, "ca");
  PRINT_TYPE(aa, "aa");
#undef PRINT_TYPE
}
