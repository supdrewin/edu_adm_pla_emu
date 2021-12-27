#pragma once

#include "launch.hpp"
#include "logo.hh"
#include "session.hpp"
#include "user.hh"

struct global {
  global() {
    splash();
    launch l;

    while (true) {
      l.new_launch();
      session new_session(l.result());
      new_session.write();
      if (new_session.should_exit())
        break;
    }
  }

  void splash() {
    printf(SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND "\n");
    CLEAR(), std::cout << logo, SLEEP(1);
  }
};
