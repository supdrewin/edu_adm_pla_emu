#pragma once

#include <cstddef>
#include <vector>

template <class _Tp> class database {
protected:
  std::vector<_Tp> data;

public:
  database() : data() {}

  size_t size() { return data.size(); }

  void add(_Tp tmp) { data.push_back(tmp); }

  bool erase(size_t index) {
    if (index >= data.size())
      return false;
    data.erase(data.begin() + index);
    return true;
  }

  void resize(size_t s) { data.resize(s); }
  void clear() { data.clear(); }

  _Tp &operator[](size_t i) { return data.operator[](i); }

  auto begin() { return data.begin(); }
  auto end() { return data.end(); }
};
