#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "database.hpp"
#include "platform.hh"
#include "user.hh"
#include "via/console.hpp"

class launch {
  enum status {
    unknown_username,
    error_passwd,
    success,
  } status;

  database db;
  user unknown;

public:
  launch() : status(), db(), unknown() {
    printf(SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND "\n");
    CLEAR();

    for (size_t i{}; status != success; ++i) {
      i == 5 ? (printf(SGR_RED_FOREGROUND SGR_BOLD
                       "Error more than 5 time, aborting...\n" SGR_RESET_ALL),
                SLEEP(1), CLEAR(), exit(EXIT_FAILURE))
             : void(0);
      ask(), judge();
    }

    printf(SGR_GREEN_FOREGROUND SGR_BOLD "Login success!!\n" SGR_RESET_ALL);
    SLEEP(1), CLEAR();
  }

  struct user result() {
    return unknown;
  }

  void ask() {
    printf("Username: ");
    std::cin >> unknown.username;
    printf("Passwd: " SGR_BLACK_FOREGROUND);
    std::cin >> unknown.passwd;
    printf(SGR_WHITE_FOREGROUND);
  }

  void judge() {
    for (auto _ : db)
      if (unknown.username == _.u.username) {
        if (unknown.passwd == _.u.passwd) {
          status = success;
          unknown.id = _.u.id;
          return;
        } else {
          status = error_passwd;
          return;
        }
      }

    status = unknown_username;
  }
};
