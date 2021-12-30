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

  void uindex_gen() {
    for (size_t i{}; i < db.size(); ++i)
      if (cur_user == db[i].user) {
        uindex = i;
        break;
      }
  }

  session(base_user u) : cur(), db(), cur_user(u), uindex() {
    uindex_gen(), (cur_user.id ? user_menu() : admin_menu());
  }

  ~session() { printf(SGR_RESET_ALL "\n"), CLEAR(); }

  bool should_exit() { return cur == finished; }

  // admin_menu.cpp
  void admin_menu();
  void admin_submenu_find();
  void admin_submenu_manage(index_t index);

  // user_menu.cpp
  void user_menu();

  // menu.cpp
  void account_settings();
  void change_passwd();

  void write() { db.write(); }

  // subject.cpp
  void add_item();
  void del_item();

  // print.cpp
  void scores_list_header();
  void print();
};
