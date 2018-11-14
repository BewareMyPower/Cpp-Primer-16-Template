// debug_rep.h
#pragma once
#include <sstream>
#include <string>

template <typename T>
inline std::string debug_rep(const T& t) {
  std::ostringstream ret;
  ret << t;
  return ret.str();
}

template <typename T>
inline std::string debug_rep(T* p) {
  std::ostringstream ret;
  ret << "pointer: " << p;
  if (p)
    ret << " " << debug_rep(*p);
  else
    ret << " null pointer";
  return ret.str();
}

inline std::string debug_rep(const std::string& s) { return '"' + s + '"'; }

inline std::string debug_rep(const char* p) {
  return ::debug_rep(std::string(p));
}
