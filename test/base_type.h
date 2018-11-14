// base_type.h
#pragma once
#include <string>
#include <type_traits>

template <typename T>
struct BaseType {
  static constexpr std::size_t size() noexcept { return sizeof(T); }

  static const char* unknownName() noexcept { return "FXXK"; }

  static constexpr bool isInt() noexcept { return std::is_integral<T>::value; }

  static const char* intType() noexcept {
    switch (size()) {
      case 1:
        return "char";
      case 2:
        return "short";
      case 4:
        return "int";
      case 8:
        return "long";
      default:
        return unknownName();
    }
  }

  static constexpr bool isSigned() noexcept { return std::is_signed<T>::value; }

  static constexpr bool isFloat() noexcept {
    return std::is_floating_point<T>::value;
  }

  static const char* floatType() noexcept {
    switch (size()) {
      case 4:
        return "float";
      case 8:
        return "double";
      case 16:
        return "long double";
      default:
        return unknownName();
    }
  }

  static std::string toString() {
    if (isInt()) {
      std::string s = isSigned() ? "" : "unsigned ";
      return s + intType();
    }
    if (isFloat()) return floatType();
    return unknownName();
  }
};

// unit test
#include <stdio.h>

inline void base_type_test() {
#define BASE_TYPE(x) BaseType<decltype(x)>::toString().data()
#define PRINT_TYPE(x, s) printf("%s is %s\n", s, BASE_TYPE(x));

    char ch = 0x01;
    unsigned char uch = ch;
    short si = ch;
    unsigned short usi = ch;
    int i = ch;
    unsigned int ui = ch;
    long l = ch;
    unsigned long ul = ch;
    float f = 0.0;
    double d = f;
    long double ld = f;

    PRINT_TYPE(ch, "ch");
    PRINT_TYPE(uch, "uch");
    PRINT_TYPE(si, "si");
    PRINT_TYPE(usi, "usi");
    PRINT_TYPE(i, "i");
    PRINT_TYPE(ui, "ui");
    PRINT_TYPE(l, "l");
    PRINT_TYPE(ul, "ul");
    PRINT_TYPE(f, "f");
    PRINT_TYPE(d, "d");
    PRINT_TYPE(ld, "ld");

#undef PRINT_TYPE
#undef BASE_TYPE
}
