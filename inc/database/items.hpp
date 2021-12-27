#pragma once

#include <fstream>
#include <string>

#include "database.hh"

struct items_database : public database<std::string> {

  void read(const char *filename = "${config}") {
    data.clear();
    std::ifstream ifs(filename);
    while (not ifs.eof()) {
      std::string tmp;
      ifs >> tmp;
      data.push_back(tmp);
    }
  }
};
