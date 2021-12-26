#pragma once

#include "database.hpp"
#include "launch.hpp"
#include "logo.hh"
#include "session.hpp"
#include "user.hh"

class gobal {
  user cur_user;

public:
  gobal() : cur_user() {
    printf(SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND "\n");
    CLEAR();
    std::cout << logo;
    SLEEP(1);

    launch new_launch;
    this->cur_user = new_launch.result();

    session new_session(cur_user);
    new_session.write();
  }
};
