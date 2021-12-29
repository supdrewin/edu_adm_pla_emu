#pragma once

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "tools/console.hh"
#include "tools/platform.hh"

#include "en_US.hh"

#define Language(LANG) using namespace LANG

struct menu {
  menu(std::vector<std::string> its, size_t width = 50)
      : items(its), width(width) {}

  void setw(size_t width) { this->width = width; }

  void show() {
    std::string outside(width, ' '), inside(width - 2, ' ');

    printf(SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND "\n"), CLEAR();
    std::cout << SGR_GREEN_BACKGROUND << outside << "\n " << SGR_RESET_ALL
              << inside << SGR_GREEN_BACKGROUND " \n " SGR_RESET_ALL;

    for (size_t i{}; i < items.size(); ++i) {
      std::string fixed((inside.size() - 6) - items[i].size(), ' ');
      printf("%3c%d. %s%s" SGR_GREEN_BACKGROUND " \n " SGR_RESET_ALL, ' ',
             static_cast<int>((i + 1) % items.size()), items[i].c_str(),
             fixed.c_str());
    }

    std::cout << inside << SGR_GREEN_BACKGROUND << " \n"
              << outside << '\n'
              << SGR_BLACK_BACKGROUND << SGR_WHITE_FOREGROUND;
  }

private:
  std::vector<std::string> items;
  size_t width;
};
