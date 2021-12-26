#pragma once

#include <cstddef>
#include <cstdio>

#include "console.hh"
#include "database.hpp"
#include "menu.hh"
#include "platform.hh"
#include "user.hh"
#include "vaild.hh"

class session {
  enum status {
    running,
    finished,
  } cur;

  database db;
  user cur_user;

public:
  size_t uindex;

  session(user u) : cur(), db(), cur_user(u), uindex() {
    uindex_gen();

    if (not cur_user.id)
      while (cur == running)
        admin_menu();
    else
      while (cur == running)
        user_menu();

    db[uindex].u = cur_user;
  }

  ~session() {
    printf(SGR_RESET_ALL "\n");
    CLEAR();
  }

  void admin_menu() {
    menu(menu_main, 7);

    int key{};
    check_cin(key);

    switch (key) {
    case 1:
      db.add(student);
      break;
    case 2:
      this->admin_submenu_find();
      break;
    case 3:
      break;
    case 4:
      this->print();
      break;
    case 5:
      this->write();
      break;
    case 6:
      this->user_settings();
      break;
    case 0:
      this->cur = finished;
      break;
    default:
      break;
    }
  }

  void admin_submenu_find() {
    menu(menu_find, 4);

    auto find_name = [](database &db) -> index_t {
      std::string name;
      std::cin >> name;
      return db.find_username(name);
    };

    auto find_number = [](database &db) -> index_t {
      size_t number;
      check_cin(number);
      return db.find_number(number);
    };

    auto find_score = [](database &db) -> index_t {
      size_t score;
      check_cin(score);
      return db.find_score(score);
    };

    int key{};
    check_cin(key);

    switch (key) {
    case 1:
      key = find_name(db);
      break;
    case 2:
      key = find_number(db);
      break;
    case 3:
      key = find_score(db);
      break;
    default:
      return;
    }

    if (key == -1) {
      printf("User not found :(\n");
      return;
    }

    admin_submenu_manage(key);
  }

  void admin_submenu_manage(index_t index) {}

  void user_menu() {
    menu(menu_user, 3);

    int key{};
    check_cin(key);

    switch (key) {
    case 1:
      this->print();
      break;
    case 2:
      user_settings();
      break;
    case 0:
      this->cur = finished;
      break;
    default:
      break;
    }
  }

  void user_settings() {
    menu(settings, 2);

    int key{};
    check_cin(key);

    switch (key) {
    case 1:
      change_passwd();
      break;
    default:
      break;
    }
  }

  bool write() { return db.write(); }

  void change_passwd() {
    std::string p1, p2;
    do {
      printf("Insert your new password: " SGR_BLACK_FOREGROUND);
      std::cin >> p1;
      printf(SGR_WHITE_FOREGROUND);
      printf("Insert previous again: " SGR_BLACK_FOREGROUND);
      std::cin >> p2;
      printf(SGR_WHITE_FOREGROUND);
    } while (p1 != p2 ? (printf("Couldn't pick your two input, "
                                "please try again :(\n"),
                         true)
                      : (printf("Password changed!!\n"), false));
    cur_user.passwd = p2;
    SLEEP(1);
  }

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
