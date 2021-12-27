#pragma once

#include <cstddef>
#include <string>
#include <vector>

enum user_identity {
  teacher = 0,
  student = 1000,
};

struct base_user {
  std::string username, passwd;
  size_t id;

  base_user(user_identity i = student) : username(), passwd(), id(i) {}

  bool operator==(base_user r) { return this->username == r.username; }
  bool operator!=(base_user r) { return this->username != r.username; }
};

struct user_data {
  base_user u;
  size_t num;
  std::vector<size_t> scores;
  user_data(user_identity i = student) : u(i), num(), scores() {}
};

struct student_data {
  base_user u;
  size_t num;
  std::vector<size_t> scores;
  student_data(user_identity i = student) : u(i), num(), scores() {}
};
