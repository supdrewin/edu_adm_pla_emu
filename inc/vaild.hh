#pragma once

#include <iostream>
#include <limits>

template <class _Tp> static void check_cin(_Tp &expr) {
  do
    std::cin >> expr;
  while (
      std::cin.fail()
          ? (std::cin.clear(),
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'),
             true)
          : false);
}
