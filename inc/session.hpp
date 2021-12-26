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
  base_user cur_user;

public:
  size_t uindex;

  session(base_user u) : cur(), db(), cur_user(u), uindex() {
    uindex_gen(), (cur_user.id ? user_menu() : admin_menu());
  }

  ~session() { printf(SGR_RESET_ALL "\n"), CLEAR(); }

  bool should_exit() { return cur == finished; }

  void admin_menu() {
    status lock{};

    while (lock == running) {
      menu(menu_main);

      int key{};
      check_cin(key);
      CLEAR();

      switch (key) {
      case 1:
        db.add();
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
      case 7:
        lock = finished;
        continue;
      case 0:
        lock = finished;
        cur = finished;
        continue;
      default:
        continue;
      }
    }
  }

  void admin_submenu_find() {
    status lock{};

    while (lock == running) {
      menu(menu_find);

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
          for (auto _ : t)
            this->print(_);
          PAUSE();
          continue;
        } else
          key = -1;
        break;
      }
      case 0:
        lock = finished;
        continue;
      default:
        continue;
      }

      if (key == -1) {
        printf("User not found :(\n"), SLEEP(1);
        continue;
      }

      admin_submenu_manage(key);
    }
  }

  void admin_submenu_manage(index_t index) {
    status lock{};

    while (lock == running) {
      menu(manage_user);

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
        print(index);
        PAUSE();
        break;
      case 2:
        modify(), uindex_gen();
        index = db.size() - 1;
        break;
      case 3:
        earse(), uindex_gen();
        lock = finished;
        continue;
      case 0:
        lock = finished;
        continue;
      default:
        continue;
      }
    }
  }

  void user_menu() {
    status lock{};

    while (lock == running) {
      menu(menu_user);

      int key{};
      check_cin(key);
      CLEAR();

      switch (key) {
      case 1:
        this->print();
        break;
      case 2:
        user_settings();
        break;
      case 3:
        lock = finished;
        continue;
      case 0:
        lock = finished;
        cur = finished;
        continue;
      default:
        continue;
      }
    }
  }

  void user_settings() {
    status lock{};

    while (lock == running) {
      menu(settings);

      int key{};
      check_cin(key);
      CLEAR();

      switch (key) {
      case 1:
        change_passwd();
        break;
      case 0:
        lock = finished;
        continue;
      default:
        continue;
      }
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
    db[uindex].u.passwd = cur_user.passwd = p2;
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
    std::cout << "student: " << db[i].u.username << "\tnumber: " << db[i].num
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
