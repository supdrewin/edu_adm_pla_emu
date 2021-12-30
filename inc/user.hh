#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "db/scores.hpp"

enum user_identity {
  teacher = 0,
  student = 1000,
};

struct base_user {
  std::string name, passwd;
  size_t id;

  base_user(user_identity i = student) : name(), passwd(), id(i) {}

  bool operator==(base_user r) { return this->name == r.name; }
  bool operator!=(base_user r) { return this->name != r.name; }
};

struct user_data {
  base_user user;
  size_t number;
  scores score;
  // std::vector<size_t> scores;
  user_data(user_identity i = student) //
      : user(i), number(), score() {}
};
