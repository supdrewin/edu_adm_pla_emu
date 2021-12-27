#pragma once

#include <fstream>
#include <string>

#include "database.hh"

struct items : public database<std::string> {
  void write(const char *filename = "${config}") {
    std::ofstream ofs(filename);
    ofs << "subjects";

    for (auto _ : data)
      ofs << '\n' << _;
  }

  void read(const char *filename = "${config}") {
    data.clear();
    std::ifstream ifs(filename);

    if (not ifs.good())
      this->write(), ifs.open(filename);

    std::string header;
    ifs >> header;

    (header == "subjects") ? void(0) : exit(1);

    while (not ifs.eof()) {
      std::string tmp;
      ifs >> tmp;
      data.push_back(tmp);
    }
  }
};
