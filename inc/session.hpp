#pragma once

#include <cstddef>
#include <cstdio>
#include <vector>

#include "console.hh"
#include "menu.hh"
#include "platform.hh"
#include "user.hh"
#include "user/database.hpp"
#include "vaild.hh"

class session {
  enum status {
    running,
    finished,
  } cur;

  user_database db;
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
    CLEAR();

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

    auto find_name = [this]() -> index_t {
      std::string name;
      printf("Name: "), std::cin >> name;
      return db.find_username(name);
    };

    auto find_number = [this]() -> index_t {
      size_t number;
      printf("Number: "), check_cin(number);
      return db.find_number(number);
    };

    auto find_score = [this]() -> std::vector<index_t> {
      size_t score;
      printf("Score: "), check_cin(score);
      return db.find_score(score);
    };

    int key{};
    check_cin(key);
    CLEAR();

    switch (key) {
    case 1:
      key = find_name();
      break;
    case 2:
      key = find_number();
      break;
    case 3: {
      auto t = find_score();
      if (t.size() == 1)
        key = t[0];
      else if (t.size() > 1) {
        key = -2;
        for (auto _ : t)
          this->print(_);
        PAUSE();
      } else
        key = -1;
      break;
    }
    default:
      return;
    }

    if (key == -1) {
      printf("User not found :(\n");
      SLEEP(1);
      return;
    }

    key >= 0 ? admin_submenu_manage(key) : void();
  }

  void admin_submenu_manage(index_t index) {
    menu(manage_user, 3);

    auto modify = [index, this]() {
      printf("Original information of this student:\n");
      this->print(index);
      db.earse(index);
      printf("Insert the new information of this student:\n");
      db.add(student);
    };

    auto earse = [index, this]() { db.earse(index); };

    int key{};
    check_cin(key);
    CLEAR();

    switch (key) {
    case 1:
      modify();
      break;
    case 2:
      earse();
      break;
    default:
      break;
    }
  }

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

  void write() { db.write(); }

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
