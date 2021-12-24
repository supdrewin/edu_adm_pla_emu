#pragma once

#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>

#include "user.hh"
#include "via/arrary.hpp"

struct user_data {
  unsigned number;
  struct user user;
  unsigned short score;

  user_data() : number(), user(), score() {}
};

class database {
  via::array<user_data> data;

public:
  database() : data() { this->read(); }

  void add() {
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
    std::ofstream fout(filename);
    if (not fout.good()) {
      return false;
    }

    for (size_t i{}; i < data.size(); ++i) {
      fout << data[i].user.username << ' ' << data[i].user.passwd << ' '
           << data[i].number << ' ' << data[i].user.id << ' ' << data[i].score
           << '\n';
    }
    return true;
  }

  bool read(const char *filename = "score.db") {
    std::ifstream fin(filename);
    if (not fin.good()) {
      this->write();
      return false;
    }
    for (size_t i{}; not fin.eof(); ++i) {
      fin >> data.at(i).user.username >> data[i].user.passwd >>
          data[i].number >> data[i].user.id >> data[i].score;
    }
    data.resize(data.size() - 1);
    return true;
  }

  auto begin() { return data.begin(); }
  auto end() { return data.end(); }
};
