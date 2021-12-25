#pragma once

#include <cstddef>
#include <cstdio>

#include "database.hpp"
#include "platform.hh"
#include "user.hh"
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
        menu();
    } else {
      this->uindex_gen();
      this->print();
    }
  }

  ~session() {
    printf(SGR_RESET_ALL "\n");
    CLEAR();
  }

  void menu() {
    int key;
    printf(SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND "\n");
    CLEAR();
    printf(
        SGR_GREEN_BACKGROUND
        "                                                  \n " SGR_RESET_ALL
        "                                                " SGR_GREEN_BACKGROUND
        " \n " SGR_RESET_ALL
        "      1. add a student                          " SGR_GREEN_BACKGROUND
        " \n " SGR_RESET_ALL
        "      2. find a student                         " SGR_GREEN_BACKGROUND
        " \n " SGR_RESET_ALL
        "      3. show database                          " SGR_GREEN_BACKGROUND
        " \n " SGR_RESET_ALL
        "      4. sync database                          " SGR_GREEN_BACKGROUND
        " \n " SGR_RESET_ALL
        "      5. exit                                   " SGR_GREEN_BACKGROUND
        " \n " SGR_RESET_ALL
        "                                                " SGR_GREEN_BACKGROUND
        " \n                                                  "
        "\n" SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND);

    std::cin >> key;
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
    case 5:
      this->cur = finished;
      break;
    default:
      break;
    }
  }

  bool write() { return db.write(); }

  void submenu_find() {}

  void uindex_gen() {
    for (size_t i{}; i < db.size(); ++i)
      if (cur_user == db[i]._user) {
        uindex = i;
        break;
      }
  }

  void print(size_t i) {
    std::cout << "student: " << db[i]._user.username
              << "\tnumber: " << db[i].number << "\tscore: " << db[i].score
              << '\n';
  }

  void print() {
    printf(SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND "\n");
    CLEAR();

    if (not cur_user.id) {
      for (size_t i{}; i < db.size(); ++i)
        if (db[i]._user.id)
          this->print(i);
      PAUSE();
      return;
    }
    this->print(uindex);
    PAUSE();
  }
};
