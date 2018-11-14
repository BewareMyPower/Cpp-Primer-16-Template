// get_arraysize.h
#pragma once

template <typename T, unsigned N>
constexpr unsigned get_arraysize(T (&a)[N]) {
  return N;
}
