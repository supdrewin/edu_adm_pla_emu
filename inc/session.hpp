#pragma once

#include <cstddef>

#include "database.hpp"
#include "user.hh"

class session {
  struct user user;
  database db;

public:
  session(struct user u) : user(u), db() {
    if (not user.id) {
      admin();
      db.add();
    } else {
      find(); // print user's score
    }
  }

  bool write() { return db.write(); }

  void admin() {}
  void find() {}
};
