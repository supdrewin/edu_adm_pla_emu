#pragma once

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "platform.hh"
#include "secure.hh"
#include "user.hh"
#include "vaild.hh"

using index_t = int;

struct user_data {
  user u;
  size_t number, score;
  user_data() : u(), number(), score() {}
};

class database {
  std::vector<user_data> data;

public:
  database() : data() { this->read(); }

  size_t size() { return this->data.size(); }

  void add(identity id) {
    user_data tmp;
    CLEAR();

  insert_username:
    printf("username: ");
    std::cin >> tmp.u.username;

    if (find_username(tmp.u.username) != -1)
      goto insert_username;

  insert_number:
    printf("number: ");
    check_cin(tmp.number);

    if (find_number(tmp.number) != -1)
      goto insert_number;

    printf("score: ");
    check_cin(tmp.score);

    tmp.u.passwd = tmp.u.username;
    tmp.u.id = (id == teacher ? 0 : 1000);
    data.push_back(tmp);
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
      if (name == _.u.username)
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
      if (_.u.id and sc == _.score)
        return i;
      ++i;
    }
    return -1;
  }

  bool write(const char *filename = "score.db") {
    std::ofstream ofs(filename);

    ofs << "username\tpasswd\tnumber\tid\tscore";
    bool default_admin{false};

    for (auto _ : data) {
      ofs << '\n'
          << _.u.username << '\t' << secure::write(_.u.passwd) << '\t'
          << _.number << '\t' << _.u.id << '\t' << _.score;

      if (not default_admin)
        default_admin = (_.u.username == "root");
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

    user_data tmp;
    for (size_t i{}; not ifs.eof(); ++i) {
      ifs >> tmp.u.username >> tmp.u.passwd >> tmp.number >> tmp.u.id >>
          tmp.score;
      secure::read(tmp.u.passwd);
      data.push_back(tmp);
    }
  }

  user_data &operator[](size_t i) { return data.operator[](i); }

  auto begin() { return data.begin(); }
  auto end() { return data.end(); }
};
