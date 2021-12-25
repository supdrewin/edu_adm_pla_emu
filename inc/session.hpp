#pragma once

#include <cstddef>
#include <cstdio>

#include "database.hpp"
#include "user.hh"

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

  void menu() {
    int key;

    printf("\x1b[32;1m##################################################\n");
    printf("#                                                #\n");
    printf("#      1. add student                            #\n");
    printf("#      2. delete student                         #\n");
    printf("#      3. exit                                   #\n");
    printf("#      4. show database                          #\n");
    printf("#      5. sync database                          #\n");
    printf("#                                                #\n");
    printf("##################################################\x1b[0m\n");

    std::cin >> key;
    switch (key) {
    case 1:
      this->db_add();
      break;
    case 2:
      this->db_earse();
      break;
    case 3:
      this->cur = finished;
      break;
    case 4:
      this->print();
      break;
    case 5:
      this->write();
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
    if (not user.id) {
      for (size_t i{}; i < db.size(); ++i)
        this->print(i);
      return;
    }
    this->print(_index);
  }
};
