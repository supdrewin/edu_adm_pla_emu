#pragma once

#include <string>

#include "platform.hh"
#include "via/console.hpp"

static const std::string menu_main[]{
    "add a student", "find a student", "show database",
    "sync database", "exit and save",
};

static const std::string menu_find[]{
    "find student name",
    "find student number",
    "find student score",
    "return to main menu",
};

static auto menu(const std::string *str, size_t num) -> void {
  printf(SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND "\n");
  CLEAR();

  printf(SGR_GREEN_BACKGROUND "%50c\n " SGR_RESET_ALL
                              "%48c" SGR_GREEN_BACKGROUND " \n " SGR_RESET_ALL,
         ' ', ' ');

  for (size_t i{}; i < num; ++i) {
    std::string tmp(42 - str[i].size(), ' ');
    printf("%3c%lu. %s%s" SGR_GREEN_BACKGROUND " \n " SGR_RESET_ALL, ' ',
           (i + 1) % num, str[i].c_str(), tmp.c_str());
  }

  printf("%48c" SGR_GREEN_BACKGROUND
         " \n%50c\n" SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND,
         ' ', ' ');
}
