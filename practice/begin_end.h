// begin_end.h

template <typename T, unsigned N>
T* begin(T (&a)[N]) {
  return a;
}

template <typename T, unsigned N>
T* end(T (&a)[N]) {
  return a + N;
}
