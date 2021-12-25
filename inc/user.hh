#pragma once

#include <string>

using user_id = size_t;

struct user {
  std::string username, passwd;
  user_id id;

  user() : username(), passwd(), id() {}

  bool operator==(user r) { return this->username == r.username; }
  bool operator!=(user r) { return this->username != r.username; }
};
