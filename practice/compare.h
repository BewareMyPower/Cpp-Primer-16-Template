// compare.h
#pragma once
#include <stdio.h>
#include <string.h>
#include <functional>

// template <typename T>
// int compare(const T& lhs, const T& rhs) {
//  printf("compare<T>(const T&, const T&) sizeof(T)=%zd\n", sizeof(T));
//  if (lhs < rhs) return -1;
//  if (rhs < lhs) return 1;
//  return 0;
//}

template <unsigned M, unsigned N>
int compare(const char (&lhs)[M], const char (&rhs)[N]) {
  printf("compare<%u,%u>(const char(&)[%u], const char(&)[%u])\n", M, N, M, N);
  return strcmp(lhs, rhs);
}

int compare(const char* lhs, const char* rhs) {
  printf("compare(const char*, const char*)\n");
  return strcmp(lhs, rhs);
}

template <typename T, typename F = std::less<T>>
int compare(const T& v1, const T& v2, F f = F()) {
  if (f(v1, v2)) return -1;
  if (f(v2, v1)) return -1;
  return 0;
}
