// sum_promote.h
#pragma once
#include <stdint.h>
#include <type_traits>

template <std::size_t size, bool is_signed>
struct promote;

template <>
struct promote<sizeof(uint8_t), false> {
  using type = uint16_t;
};

template <>
struct promote<sizeof(uint16_t), false> {
  using type = uint32_t;
};

template <>
struct promote<sizeof(uint32_t), false> {
  using type = uint64_t;
};

template <>
struct promote<sizeof(int8_t), true> {
  using type = int16_t;
};

template <>
struct promote<sizeof(int16_t), true> {
  using type = int32_t;
};

template <>
struct promote<sizeof(int32_t), true> {
  using type = int64_t;
};

template <typename T>
auto sum(T x, T y) ->
    typename promote<sizeof(T), std::is_signed<T>::value>::type {
  using return_type =
      typename promote<sizeof(T), std::is_signed<T>::value>::type;
  return static_cast<return_type>(x) + y;
}
// template <typename T>
// auto sum(T x, T y) -> typename promote<T>::type {
//  return static_cast<typename promote<T>::type>(x) + y;
//}
