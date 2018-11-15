// print.h
#pragma once
#include <iostream>

template <typename T>
std::ostream& print(std::ostream& os, const T& t) {
  os << t;
  return os << std::endl;
}

template <typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, Args... args) {
  os << t << ", ";
  return print(os, args...);
}
