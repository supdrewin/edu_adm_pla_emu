#pragma once

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "platform.hh"
#include "secure.hh"
#include "user.hh"
#include "vaild.hh"
#include "via/array.hpp"

using index_t = int;

struct user_data {
  user _user;
  size_t number, score;
  user_data() : _user(), number(), score() {}
};

class database {
  via::array<user_data> data;

public:
  database() : data() { this->read(); }

  size_t size() { return this->data.size(); }

  void add(identity id) {
    CLEAR();
    size_t num{}, i{data.size()};
    std::string name;

  insert_username:
    printf("username: ");
    std::cin >> name;

    if (find_username(name) != -1)
      goto insert_username;

  insert_number:
    printf("number: ");
    check_cin(num);

    if (find_number(num) != -1)
      goto insert_number;

    printf("score: ");
    check_cin(data.at(i).score);

    data[i]._user.username = data[i]._user.passwd = name;
    data[i]._user.id = (id == teacher ? 0 : 1000);
    data[i].number = num;
  }

  bool earse(size_t index) {
    if (index >= data.size())
      return false;
    for (size_t i{index}; i + 1 < data.size(); ++i)
      data[i] = data[i + 1];
    data.resize(data.size() - 1);
    return true;
  }

  index_t find_username(std::string name) {
    size_t i{};
    for (auto _ : data) {
      if (name == _._user.username)
        return i;
      ++i;
    }
    return -1;
  }

  index_t find_number(size_t num) {
    size_t i{};
    for (auto _ : data) {
      if (num == _.number)
        return i;
      ++i;
    }
    return -1;
  }

  index_t find_score(size_t sc) {
    size_t i{};
    for (auto _ : data) {
      if (_._user.id and sc == _.score)
        return i;
      ++i;
    }
    return -1;
  }

  bool write(const char *filename = "score.db") {
    std::ofstream ofs(filename);

    ofs << "username\tpasswd\tnumber\tid\tscore";
    bool default_admin{false};

    for (size_t i{}; i < data.size(); ++i) {
      ofs << '\n'
          << data[i]._user.username << '\t'
          << secure::write(data[i]._user.passwd) << '\t' << data[i].number
          << '\t' << data[i]._user.id << '\t' << data[i].score;

      if (not default_admin)
        default_admin = (data[i]._user.username == "root");
    }

    if (not default_admin)
      ofs << "\nroot\t" << secure::write("root") << "\t0\t0\t0";
    return true;
  }

  void read(const char *filename = "score.db") {
    std::ifstream ifs(filename);
    if (not ifs.good())
      this->write();

    std::string header[5];
    for (auto &_ : header)
      ifs >> _;

    (header[0] == "username" and header[1] == "passwd" and
     header[2] == "number" and header[3] == "id" and header[4] == "score")
        ? void(0)
        : exit(1);

    for (size_t i{}; not ifs.eof(); ++i) {
      ifs >> data.at(i)._user.username >> data[i]._user.passwd >>
          data[i].number >> data[i]._user.id >> data[i].score;
      secure::read(data[i]._user.passwd);
    }
  }

  auto operator[](size_t i) { return data.operator[](i); }

  auto begin() { return data.begin(); }
  auto end() { return data.end(); }
};
