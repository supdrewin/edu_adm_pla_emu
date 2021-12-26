#pragma once

#include <cstddef>
#include <vector>

template <class _Tp> class _database {
protected:
  std::vector<_Tp> data;

public:
  size_t size() { return this->data.size(); }

  void add(_Tp tmp) { data.push_back(tmp); }

  bool earse(size_t index) {
    if (index >= data.size())
      return false;
    for (size_t i{index}; i + 1 < data.size(); ++i)
      data[i] = data[i + 1];
    data.resize(data.size() - 1);
    return true;
  }

  _Tp &operator[](size_t i) { return data.operator[](i); }

  auto begin() { return data.begin(); }
  auto end() { return data.end(); }
};
