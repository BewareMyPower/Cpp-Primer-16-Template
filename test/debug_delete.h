// debug_delete.h
#pragma once
#include <iostream>

// unique_ptr的删除器，用于在析构时打印信息
class DebugDelete {
 public:
  DebugDelete(std::ostream& s = std::cerr) : os(s) {}

  template <typename T>
  void operator()(T* p) const {
    os << "deleting unique_ptr<T> sizeof(T)=" << sizeof(T) << std::endl;
    delete p;
  }

 private:
  std::ostream& os;
};
