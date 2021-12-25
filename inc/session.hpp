#pragma once

#include <cstddef>

#include "database.hpp"
#include "user.hh"

class session {
  struct user user;
  database db;
  size_t _index;

public:
  session(struct user u) : user(u), db(), _index() {
    if (not user.id) {
      admin();

    } else {
      this->index();
      this->print();
    }
  }

  bool write() { return db.write(); }

  void db_add() { db.add(); }

  void admin() { this->db_add(); }

  // normal
  void index() {
    for (size_t i{}; i < db.size(); ++i)
      if (user == db[i].user) {
        _index = i;
        break;
      }
  }

  void print() {
    std::cout << "student: " << db[_index].user.username
              << "\tnumber: " << db[_index].number
              << "\tscore: " << db[_index].score;
  }
};
