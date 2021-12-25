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
    CLEAR();
    std::cout << logo;
    PAUSE();
    launch new_launch;
    this->cur_user = new_launch.result();

    session new_session(cur_user);
    new_session.write();
  }
};
