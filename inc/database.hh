#pragma once

#include <cstddef>
#include <vector>

template <class _Tp> class database {
protected:
  std::vector<_Tp> data;

public:
  database() : data() {}

  size_t size() { return this->data.size(); }

  void add(_Tp tmp) { data.push_back(tmp); }

  bool earse(size_t index) {
    if (index >= data.size())
      return false;
    data.erase(data.begin() + index);
    return true;
  }

  _Tp &operator[](size_t i) { return data.operator[](i); }

  auto begin() { return data.begin(); }
  auto end() { return data.end(); }
};
