#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "database.hpp"
#include "platform.hh"
#include "user.hh"
#include "via/console.hpp"

enum launch_status { unknown_username, error_passwd, success };

class launch {
  launch_status status;
  struct user user;
  database db;

public:
  launch() : status(), user(), db() {
    printf(SGR_WHITE_BACKGROUND SGR_BLACK_FOREGROUND "\n");
    CLEAR();

    for (size_t i{}; status != launch_status::success; ++i) {
      i == 5 ? printf("\x1b[31;1mError more than 5 time, aborting...\x1b[0m\n"),
          exit(EXIT_FAILURE) : void(0);
      ask(), judge();
    }

    printf("\x1b[32;1mLogin success!!\x1b[0m\n");
    SLEEP(1), CLEAR();
  }

  struct user result() {
    return user;
  }

  void ask() {
    printf("Username: ");
    std::cin >> user.username;
    printf("Passwd: " SGR_WHITE_FOREGROUND);
    std::cin >> user.passwd;
    printf(SGR_BLACK_FOREGROUND);
  }

  void judge() {
    if (user.username == "root")
      if (user.passwd == "root") {
        status = launch_status::success;
        return;
      }

    for (auto _ : db)
      if (user.username == _.user.username) {
        if (user.passwd == _.user.passwd) {
          status = launch_status::success;
          user.id = _.user.id;
          return;
        } else {
          status = launch_status::error_passwd;
          return;
        }
      }

    status = launch_status::unknown_username;
  }
};
