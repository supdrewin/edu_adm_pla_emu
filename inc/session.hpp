#pragma once

#include <cstddef>
#include <cstdio>

#include "database.hpp"
#include "platform.hh"
#include "user.hh"
#include "via/console.hpp"

class session {
  struct user user;
  database db;
  size_t _index;

  enum status {
    finished,
    running,
  } cur;

public:
  session(struct user u) : user(u), db(), _index(), cur(running) {
    if (not user.id) {
      while (cur == running)
        menu();
    } else {
      this->index();
      this->print();
    }
  }

  ~session() {
    printf(SGR_RESET_ALL "\n");
    CLEAR();
  }

  void menu() {
    int key;
    printf(SGR_WHITE_BACKGROUND SGR_BLACK_FOREGROUND "\n");
    CLEAR();
    printf(
        SGR_GREEN_BACKGROUND
        "                                                  \n " SGR_RESET_ALL
        "                                                " SGR_GREEN_BACKGROUND
        " \n " SGR_RESET_ALL
        "      1. add student                            " SGR_GREEN_BACKGROUND
        " \n " SGR_RESET_ALL
        "      2. delete student                         " SGR_GREEN_BACKGROUND
        " \n " SGR_RESET_ALL
        "      3. show database                          " SGR_GREEN_BACKGROUND
        " \n " SGR_RESET_ALL
        "      4. sync database                          " SGR_GREEN_BACKGROUND
        " \n " SGR_RESET_ALL
        "      5. exit                                   " SGR_GREEN_BACKGROUND
        " \n " SGR_RESET_ALL
        "                                                " SGR_GREEN_BACKGROUND
        " \n                                                  "
        "\n" SGR_WHITE_BACKGROUND SGR_BLACK_FOREGROUND);

    std::cin >> key;
    switch (key) {
    case 1:
      this->db_add();
      break;
    case 2:
      this->db_earse();
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

  void db_add() { db.add(); }
  void db_earse() { db.earse(); }

  void admin() { this->db_add(); }

  // normal
  void index() {
    for (size_t i{}; i < db.size(); ++i)
      if (user == db[i].user) {
        _index = i;
        break;
      }
  }

  void print(size_t i) {
    std::cout << "student: " << db[i].user.username
              << "\tnumber: " << db[i].number << "\tscore: " << db[i].score
              << '\n';
  }

  void print() {
    printf(SGR_WHITE_BACKGROUND SGR_BLACK_FOREGROUND "\n");
    CLEAR();

    if (not user.id) {
      for (size_t i{}; i < db.size(); ++i)
        this->print(i);
      PAUSE();
      return;
    }
    this->print(_index);
    PAUSE();
  }
};
