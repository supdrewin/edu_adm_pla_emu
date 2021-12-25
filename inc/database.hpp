#pragma once

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "platform.hh"
#include "secure.hh"
#include "user.hh"
#include "via/array.hpp"

struct user_data {
  unsigned number;
  struct user user;
  unsigned short score;

  size_t key;

  user_data() : number(), user(), score(), key() {}
};

class database {
  via::array<user_data> data;

public:
  database() : data() { this->read(); }

  size_t size() { return this->data.size(); }

  void add() {
    CLEAR();
    auto i{data.size()};
    printf("username: ");
    std::cin >> data.at(i).user.username;
    printf("passwd: ");
    std::cin >> data[i].user.passwd;
    printf("number: ");
    std::cin >> data[i].number;
    printf("id: ");
    std::cin >> data[i].user.id;
    printf("score: ");
    std::cin >> data[i].score;
  }
  void earse() {}

  bool write(const char *filename = "score.db") {
    std::ofstream ofs(filename);

    ofs << "username\tpasswd\tnumber\tid\tscore";
    bool default_admin{false};

    for (size_t i{}; i < data.size(); ++i) {
      ofs << '\n'
          << data[i].user.username << '\t' << secure::write(data[i].user.passwd)
          << '\t' << data[i].number << '\t' << data[i].user.id << '\t'
          << data[i].score;

      if (not default_admin)
        default_admin = data[i].user.username == "root";
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

    not(header[0] == "username" and header[1] == "passwd" and
        header[2] == "number" and header[3] == "id" and header[4] == "score")
        ? exit(EXIT_FAILURE)
        : void();

    for (size_t i{}; not ifs.eof(); ++i) {
      ifs >> data.at(i).user.username >> data[i].user.passwd >>
          data[i].number >> data[i].user.id >> data[i].score;
      secure::read(data[i].user.passwd);
    }
  }

  auto operator[](size_t i) { return data.operator[](i); }

  auto begin() { return data.begin(); }
  auto end() { return data.end(); }
};
