#pragma once

#if defined(__has_menu)

#include <string>
#include <vector>

#include "tools/console.hh"
#include "tools/platform.hh"

#include "en_US.hh"

#define LANG(lang) using namespace lang;

static void menu(const std::vector<std::string> str) {
  printf(SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND "\n");
  CLEAR();

  printf(SGR_GREEN_BACKGROUND "%50c\n " SGR_RESET_ALL
                              "%48c" SGR_GREEN_BACKGROUND " \n " SGR_RESET_ALL,
         ' ', ' ');

  for (size_t i{}; i < str.size(); ++i) {
    std::string tmp(42 - str[i].size(), ' ');
    printf("%3c%d. %s%s" SGR_GREEN_BACKGROUND " \n " SGR_RESET_ALL, ' ',
           static_cast<int>((i + 1) % str.size()), str[i].c_str(), tmp.c_str());
  }

  printf("%48c" SGR_GREEN_BACKGROUND
         " \n%50c\n" SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND,
         ' ', ' ');
}

#endif // defined (__has_menu)
