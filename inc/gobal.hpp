#pragma once

#include "database.hpp"
#include "launch.hpp"
#include "session.hpp"
#include "user.hh"

class gobal {
  struct user user;

public:
  gobal() : user() {
    auto new_launch = new launch;
    this->user = new_launch->result();
    delete new_launch;
    session new_session(user);
    new_session.write();
  }
};