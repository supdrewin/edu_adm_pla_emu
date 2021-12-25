#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "database.hpp"
#include "platform.hh"
#include "user.hh"

enum launch_status { unknown_username, error_passwd, success };

class launch {
  launch_status status;
  struct user user;
  database db;

public:
  launch() : status(), user(), db() {
    __clear();

    for (size_t i{}; status != launch_status::success; ++i) {
      i == 5 ? printf("\x1b[31;1mError more than 5 time, aborting...\x1b[0m\n"),
          exit(EXIT_FAILURE) : void(0);
      ask(), judge();
    }

    printf("\x1b[32;1mLogin success!!\x1b[0m\n");
    __sleep(1), __clear();
  }

  struct user result() {
    return user;
  }

  void ask() {
    printf("\x1b[33;1mUsername:\x1b[0m ");
    std::cin >> user.username;
    printf("\x1b[33;1mPasswd:\x1b[0m ");
    std::cin >> user.passwd;
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
