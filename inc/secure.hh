#pragma once

#include <string>

#include "console.hh"

namespace secure {

inline auto read(std::string &passwd) {
  for (auto &_ : passwd)
    _ -= ESC;
}

inline auto write(std::string passwd) {
  auto tmp(passwd);
  for (auto &_ : tmp)
    _ += ESC;
  return tmp;
}

}; // namespace secure
