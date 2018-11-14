// Blob.h: 定义了Blob类模板和BlobPtr类模板，分别为vector<T>的值语义和指针语义
// 分别维护了shared_ptr<vector<T>>和weak_ptr<vector<T>>
#pragma once
#include <memory>
#include <string>
#include <vector>

template <typename>
class BlobPtr;

template <typename>
class Blob;

template <typename T>
static bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T>
class Blob {
  friend class BlobPtr<T>;
  friend bool operator==<T>(const Blob<T>&, const Blob<T>&);

 public:
  using value_type = T;
  using size_type = typename std::vector<T>::size_type;

  Blob();
  Blob(std::initializer_list<T> il);

  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }

  void push_back(const T& t) { data->push_back(t); }
  void push_back(T&& t) { data->push_back(std::move(t)); }
  void pop_back();

  typename std::vector<T>::iterator begin() { return data->begin(); }
  typename std::vector<T>::iterator end() { return data->end(); }

  typename std::vector<T>::const_iterator cbegin() const { return data->cbegin(); }
  typename std::vector<T>::const_iterator cend() const { return data->cend(); }

  T& back();
  T& operator[](size_type i);

 private:
  std::shared_ptr<std::vector<T>> data;

  // 若下标i不合法，则抛出由msg构造的异常
  void check(size_type i, const std::string& msg);
};

// 若试图访问一个不存在的元素，BlobPtr抛出一个异常
template <typename T>
class BlobPtr {
 public:
  BlobPtr() = default;
  BlobPtr(Blob<T>& a, size_t sz = 0) : wptr(a.data), curr(sz) {}

  BlobPtr(const BlobPtr& rhs) : wptr(rhs.wptr), curr(rhs.curr) {}
  BlobPtr(BlobPtr&& rhs) noexcept : wptr(rhs.wptr), curr(rhs.curr) {}

  BlobPtr& operator=(const BlobPtr& rhs) {
    if (this != &rhs) {
      wptr = rhs.wptr;
      curr = rhs.curr;
    }
    return *this;
  }

  BlobPtr& operator=(BlobPtr&& rhs) noexcept {
    wptr = rhs.wptr;
    curr = rhs.curr;
    return *this;
  }

  T& operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
  }

  T* operator->() const { return &this->operator*(); }

  T& operator[](std::size_t i) {
    auto p = check(curr + i, "subscript out of range");
    return (*p)[curr + i];
  }

  const T& operator[](std::size_t i) const {
    return static_cast<const T&>(
        const_cast<const BlobPtr<T>&>(*this).operator[](i));
  }

  // 前置运算符
  BlobPtr& operator++();
  BlobPtr& operator--();

  // 后置运算符
  BlobPtr operator++(int);
  BlobPtr operator--(int);

 private:
  std::weak_ptr<std::vector<T>> wptr;
  std::size_t curr = 0;

  // 若检查成功，返回一个指向vector的shared_ptr；否则抛出由msg构造的异常
  std::shared_ptr<std::vector<T>> check(std::size_t i,
                                        const std::string& msg) const;
};

template <typename T>
static bool operator==(const Blob<T>& lhs, const Blob<T>& rhs) {
  return lhs.data == rhs.data;
}

template <typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) {}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il)
    : data(std::make_shared<std::vector<T>>(il)) {}

template <typename T>
inline void Blob<T>::check(size_type i, const std::string& msg) {
  if (i >= data->size()) throw std::out_of_range(msg);
}

template <typename T>
inline T& Blob<T>::back() {
  check(0, "back on empty Blob");
  return data->back();
}

template <typename T>
inline T& Blob<T>::operator[](size_type i) {
  check(i, "subscript out of range");
  return (*data)[i];
}

template <typename T>
inline void Blob<T>::pop_back() {
  check(0, "pop_back on empty Blob");
  data->pop_back();
}

template <typename T>
inline std::shared_ptr<std::vector<T>> BlobPtr<T>::check(
    std::size_t i, const std::string& msg) const {
  auto sptr = wptr.lock();
  if (!sptr) throw std::runtime_error("unbounded BlobPtr");

  if (i >= sptr->size()) throw std::out_of_range(msg);
  return sptr;
}

template <typename T>
inline BlobPtr<T>& BlobPtr<T>::operator++() {
  check(curr, "operator++ past end of BlobPtr");
  ++curr;
  return *this;
}

template <typename T>
inline BlobPtr<T>& BlobPtr<T>::operator--() {
  --curr;
  check(curr, "operator-- past begin of BlobPtr");
  return *this;
}

template <typename T>
inline BlobPtr<T> BlobPtr<T>::operator++(int) {
  auto ret = *this;
  ++*this;
  return ret;
}

template <typename T>
inline BlobPtr<T> BlobPtr<T>::operator--(int) {
  auto ret = *this;
  --*this;
  return ret;
}
