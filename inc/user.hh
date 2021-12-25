#pragma once

#include <cstddef>
#include <string>

enum identity {
  teacher,
  student,
};

struct user {
  std::string username, passwd;
  size_t id;

  user() : username(), passwd(), id() {}

  bool operator==(user r) { return this->username == r.username; }
  bool operator!=(user r) { return this->username != r.username; }
};
