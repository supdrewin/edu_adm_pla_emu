#pragma once

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "database.hh"
#include "platform.hh"
#include "secure.hh"
#include "user.hh"
#include "vaild.hh"

using index_t = int;

class user_database : public database<user_data> {
  std::vector<std::string> items;

public:
  user_database() : items() { this->read(); }

  void add(user_identity id = student) {
    user_data tmp{id};

  insert_username:
    printf("username: ");
    std::cin >> tmp.u.username;

    if (find_username(tmp.u.username) != -1)
      goto insert_username;

  insert_number:
    printf("number: ");
    check_cin(tmp.num);

    if (find_number(tmp.num) != -1)
      goto insert_number;

    printf("scores:\n");
    tmp.score.resize(items.size());
    for (size_t i{}; i < items.size(); ++i) {
      printf("%s: ", items[i].c_str());
      check_cin(tmp.score[i]);
    }

    tmp.u.passwd = tmp.u.username;
    data.push_back(tmp);
  }

  index_t find_username(std::string name) {
    index_t i{};
    for (auto _ : data) {
      if (name == _.u.username)
        return i;
      ++i;
    }
    return -1;
  }

  index_t find_number(size_t num) {
    index_t i{};
    for (auto _ : data) {
      if (num == _.num)
        return i;
      ++i;
    }
    return -1;
  }

  std::vector<index_t> find_score(size_t sc) {
    std::vector<index_t> tmp;
    index_t i{};
    for (auto _ : data) {
      if (_.u.id and sc == _.score[0])
        tmp.push_back(i);
      ++i;
    }
    return tmp;
  }

  void write(const char *filename = "${database}") {
    std::ofstream ofs(filename);

    ofs << "username\tpasswd\tnumber\tid\tscores";
    bool default_admin{false};

    for (auto _ : data) {
      ofs << '\n'
          << _.u.username << '\t' << secure::write(_.u.passwd) << '\t' << _.num
          << '\t' << _.u.id;

      for (auto __ : _.score)
        ofs << '\t' << __;

      if (not default_admin)
        default_admin = (_.u.username == "root");
    }

    if (not default_admin) {
      ofs << "\nroot\t" << secure::write("root") << "\t0\t0";
      for (size_t i{}; i < items.size(); ++i)
        ofs << "\t0";
    }
  }

  void read(const char *filename = "${database}") {
    read_config();

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
      ifs >> tmp.u.username >> tmp.u.passwd >> tmp.num >> tmp.u.id;
      tmp.score.resize(items.size());
      for (size_t j{}; j < items.size(); ++j)
        ifs >> tmp.score[j];
      secure::read(tmp.u.passwd);
      data.push_back(tmp);
    }
  }

  void read_config(const char *filename = "${config}") {
    items.clear();
    std::ifstream ifs(filename);
    while (not ifs.eof()) {
      std::string tmp;
      ifs >> tmp;
      items.push_back(tmp);
    }
  }

  void print(size_t i) {
    printf("student: %s\tnumber: %d\t", data[i].u.username.c_str(),
           static_cast<int>(data[i].num));
    this->print_scores(i);
    printf("\n");
  }

  void print_scores(size_t i) {
    printf("scores:");
    for (size_t j{}; j < items.size(); ++j)
      printf(" %s: %d", items[j].c_str(), static_cast<int>(data[i].score[j]));
  }

  void clear() { data.clear(); }
};
