#include "session.hpp"

void session::account_settings() {
  status lock{};
  menu m(settings);

  while (lock == running) {
    m.show();

    int key{};
    check_cin(key);
    CLEAR();

    switch (key) {
    case 1:
      change_passwd();
      break;
    case 0:
      lock = finished;
      continue;
    default:
      continue;
    }
  }
}

void session::change_passwd() {
  std::string p1, p2;
  do {
    printf("Insert your new password: " SGR_BLACK_FOREGROUND);
    std::cin >> p1;
    printf(SGR_WHITE_FOREGROUND);
    printf("Insert previous again: " SGR_BLACK_FOREGROUND);
    std::cin >> p2;
    printf(SGR_WHITE_FOREGROUND);
  } while (p1 == p2 ? (p2.size() < 6 ? (printf("Password's length must >= 6, "
                                               "please try another :(\n"),
                                        true)
                                     : (printf("Password changed!!\n"), false))
                    : (printf("Couldn't pick your two input, "
                              "please try again :(\n"),
                       true));
  db[uindex].user.passwd = cur_user.passwd = p2;
  SLEEP(1);
}
