#include "session.hpp"

void session::user_menu() {
  {
    status lock{};
    menu m(menu_user);

    while (lock == running) {
      m.show();

      int key{};
      check_cin(key);
      CLEAR();

      switch (key) {
      case 1:
        this->print();
        break;
      case 2:
        account_settings();
        break;
      case 3:
        lock = finished;
        continue;
      case 0:
        lock = finished;
        cur = finished;
        continue;
      default:
        continue;
      }
    }
  }
}
