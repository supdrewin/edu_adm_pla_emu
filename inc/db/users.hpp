#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "database.hh"
#include "user.hh"

#include "db/items.hpp"

#include "tools/platform.hh"
#include "tools/secure.hh"
#include "tools/types.hh"
#include "tools/vaild.hh"

struct user_db : public database<user_data> {
  std::string filename;
  items its;

  user_db(const char *name) : filename(name), its("subject.db") {
    this->read();
  }

  void add_user(user_identity id = student) {
    user_data tmp{id};
    printf(SGR_BOLD);

  insert_username:
    printf("username: ");
    std::cin >> tmp.user.name;

    if (find_username(tmp.user.name) != -1)
      goto insert_username;

  insert_number:
    printf("number: ");
    check_cin(tmp.number);

    if (find_number(tmp.number) != -1)
      goto insert_number;

    printf("scores:\n");
    tmp.score.resize(its.size() + 1);
    for (size_t i{}; i < its.size();) {
      printf("%s: ", its[i].c_str());
      check_cin(tmp.score[++i]);
      tmp.score[0] += tmp.score[i];
    }

    tmp.user.passwd = tmp.user.name;
    data.push_back(tmp);
  }

  void add_item(std::string it) {
    its.add(it);
    size_t score;
    for (auto &_ : data) {
      _.user.id ? (printf("%s: ", _.user.name.c_str()), check_cin(score),
                   _.score[0] += score, _.score.add(score))
                : _.score.add(0);
    }
  }

  bool del_item(std::string it) {
    for (size_t i{}; i < its.size(); ++i)
      if (it == its[i].data()) {
        its.erase(i);
        for (auto &_ : data) {
          _.score[0] -= _.score[i + 1];
          _.score.erase(i + 1);
        }
        return true;
      }
    return false;
  }

  index_t find_username(std::string name) {
    int count{}, c{};
    index_t index{-1};
    for (size_t i{}; i < data.size(); ++i, c = 0) {
      for (size_t j{}; j < std::min(name.size(), data[i].user.name.size()); ++j)
        (name[j] == data[i].user.name[j]) ? ++c : --c;
      if (c == static_cast<int>(data[i].user.name.size()))
        return i;
      c -= (name.size() - data[i].user.name.size()) > 0
               ? (name.size() - data[i].user.name.size())
               : 0;
      if (c > count)
        count = c, index = i;
    }
    return index;
  }

  index_t find_number(size_t num) {
    index_t i{};
    for (auto _ : data) {
      if (num == _.number)
        return i;
      ++i;
    }
    return -1;
  }

  std::vector<index_t> find_score(size_t sc) {
    std::vector<index_t> tmp;
    index_t i{};
    for (auto _ : data) {
      if (_.user.id and sc == _.score[0])
        tmp.push_back(i);
      ++i;
    }
    return tmp;
  }

  void write() {
    its.write();
    std::ofstream ofs(filename);

    ofs << "username\tpasswd\tnumber\tid\tscores";
    bool default_admin{false};

    for (auto _ : data) {
      ofs << '\n'
          << _.user.name << '\t' << secure::write(_.user.passwd) << '\t'
          << _.number << '\t' << _.user.id;

      for (auto __ : _.score)
        ofs << '\t' << __;

      if (not default_admin)
        default_admin = (_.user.name == "root");
    }

    if (not default_admin) {
      ofs << "\nroot\t" << secure::write("root") << "\t0\t0";
      for (size_t i{}; i < its.size(); ++i)
        ofs << "\t0";
    }
  }

  void read() {
    its.read(), this->clear();

    std::ifstream ifs(filename);
    if (not ifs.good())
      this->write(), ifs.open(filename);

    std::string header[5];
    for (auto &_ : header)
      ifs >> _;

    (header[0] == "username" and header[1] == "passwd" and
     header[2] == "number" and header[3] == "id" and header[4] == "scores")
        ? void(0)
        : exit(1);

    user_data tmp;
    for (size_t i{}; not ifs.eof(); ++i) {
      ifs >> tmp.user.name >> tmp.user.passwd >> tmp.number >> tmp.user.id;
      tmp.score.resize(its.size() + 1);
      for (size_t j{}; j < its.size() + 1; ++j)
        ifs >> tmp.score[j];
      secure::read(tmp.user.passwd);
      data.push_back(tmp);
    }
  }

  void print_user(size_t i) {
    printf("|%9s  |%11d |", data[i].user.name.c_str(),
           static_cast<int>(data[i].number));
    this->print_scores(i);
  }

  void print_scores(size_t i) {
    for (size_t j{}; j < its.size() + 1; ++j)
      printf("%8d  |", static_cast<int>(data[i].score[j]));
    printf("\n");
  }
};
