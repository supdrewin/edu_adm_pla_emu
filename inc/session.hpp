#pragma once

#include <cstddef>
#include <cstdio>

#include "database.hpp"
#include "menu.hh"
#include "platform.hh"
#include "user.hh"
#include "vaild.hh"
#include "via/console.hpp"

class session {
  enum status {
    running,
    finished,
  } cur;

  database db;
  user cur_user;

public:
  size_t uindex;

  session(struct user u) : cur(), db(), cur_user(u), uindex() {
    if (not cur_user.id) {
      while (cur == running)
        admin_menu();
    } else {
      this->uindex_gen();
      this->print();
    }
  }

  ~session() {
    printf(SGR_RESET_ALL "\n");
    CLEAR();
  }

  void admin_menu() {
    menu(menu_main, 5);

    int key{};
    check_cin(key);

    switch (key) {
    case 1:
      db.add(student);
      break;
    case 2:
      this->submenu_find();
      break;
    case 3:
      this->print();
      break;
    case 4:
      this->write();
      break;
    case 0:
      this->cur = finished;
      break;
    default:
      break;
    }
  }

  void submenu_find() {
    menu(menu_find, 4);

    int key{};
    check_cin(key);
    switch (key) {
    default:
      break;
    }
  }

  bool write() { return db.write(); }

  void uindex_gen() {
    for (size_t i{}; i < db.size(); ++i)
      if (cur_user == db[i].u) {
        uindex = i;
        break;
      }
  }

  void print(size_t i) {
    std::cout << "student: " << db[i].u.username << "\tnumber: " << db[i].number
              << "\tscore: " << db[i].score << '\n';
  }

  void print() {
    printf(SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND "\n");
    CLEAR();

    if (not cur_user.id) {
      for (size_t i{}; i < db.size(); ++i)
        if (db[i].u.id)
          this->print(i);
      PAUSE();
      return;
    }
    this->print(uindex);
    PAUSE();
  }
};
