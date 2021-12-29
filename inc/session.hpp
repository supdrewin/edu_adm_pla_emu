#pragma once

#include <cstddef>
#include <cstdio>
#include <vector>

#include "db/users.hpp"
#include "tools/console.hh"
#include "tools/platform.hh"
#include "tools/vaild.hh"
#include "user.hh"

#include "tui/menu.hh"
Language(en_US);

class session {
  enum status {
    running,
    finished,
  } cur;

  user_db db;
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
    menu m(menu_main);

    while (lock == running) {
      m.show();

      int key{};
      check_cin(key);
      CLEAR();

      switch (key) {
      case 1:
        db.add_user();
        break;
      case 2:
        this->admin_submenu_find();
        break;
      case 3:
        this->add_item();
        break;
      case 4:
        this->del_item();
        break;
      case 5:
        this->print();
        break;
      case 6:
        this->write();
        break;
      case 7:
        this->user_settings();
        break;
      case 8:
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
    menu m(menu_find);

    while (lock == running) {
      m.show();

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
            db.print_user(_);
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
    menu m(manage_user);

    while (lock == running) {
      m.show();

      auto modify = [index, this]() {
        printf("Original information of this student:\n");
        scores_list_header();
        db.print_user(index);
        db.erase(index);
        printf(SGR_WHITE_FOREGROUND SGR_UNDERLINE_OFF "\n");
        printf("Insert the new information of this student:\n");
        db.add_user(student);
      };

      auto earse = [index, this]() { db.erase(index); };

      int key{};
      check_cin(key);
      CLEAR();

      switch (key) {
      case 1:
        scores_list_header();
        db.print_user(index);
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
    menu m(menu_user);

    while (lock == running) {
      m.show();

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
    menu m(settings);

    while (lock == running) {
      m.show();

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

  void add_item() {
    std::string item;
    printf("The subject you want to add: "), std::cin >> item;
    db.add_item(item), printf("Success!!\n"), SLEEP(1);
  }

  void del_item() {
    std::string item;
    printf("The subject you want to delete: "), std::cin >> item;
    db.del_item(item) ? printf("Success!!\n") : printf("Failed!!\n");
    SLEEP(1);
  }

  void change_passwd() {
    std::string p1, p2;
    do {
      printf("Insert your new password: " SGR_BLACK_FOREGROUND);
      std::cin >> p1;
      printf(SGR_WHITE_FOREGROUND);
      printf("Insert previous again: " SGR_BLACK_FOREGROUND);
      std::cin >> p2;
      printf(SGR_WHITE_FOREGROUND);
    } while (p1 == p2
                 ? (p2.size() < 6 ? (printf("Password's length must >= 6, "
                                            "please try another :(\n"),
                                     true)
                                  : (printf("Password changed!!\n"), false))
                 : (printf("Couldn't pick your two input, "
                           "please try again :(\n"),
                    true));
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

  void scores_list_header() {
    printf(SGR_BOLD SGR_GREEN_FOREGROUND SGR_UNDERLINE_ON);

    size_t count{db.its.size() * 11 + 12};
    if (cur_user.id == teacher)
      count += 25;
    while (count--)
      printf(" ");

    printf("\n|");
    if (cur_user.id == teacher)
      printf("  student  |   number   |");
    printf("    all   |");
    for (auto _ : db.its)
      printf("%8s  |", _.c_str());
    printf(SGR_MAGENTA_FOREGROUND "\n");

    cur_user.id == student ? printf("|") : 0;
  }

  void print() {
    printf(SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND "\n"), CLEAR();
    scores_list_header();

    if (not cur_user.id) {
      for (size_t i{}; i < db.size(); ++i)
        if (db[i].u.id)
          db.print_user(i);
      PAUSE();
      return;
    }

    db.print_scores(uindex), PAUSE();
  }
};
