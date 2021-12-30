#include "session.hpp"

void session::admin_menu() {
  status lock{};
  menu m(menu_main);

  while (lock == running) {
    m.show();

    int key{};
    check_cin(key);
    CLEAR();

    switch (key) {
    case 1:
      db.add_user();
      break;
    case 2:
      this->admin_submenu_find();
      break;
    case 3:
      this->add_item();
      break;
    case 4:
      this->del_item();
      break;
    case 5:
      this->print();
      break;
    case 6:
      this->write();
      break;
    case 7:
      this->account_settings();
      break;
    case 8:
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

void session::admin_submenu_find() {
  status lock{};
  menu m(menu_find);

  while (lock == running) {
    m.show();

    auto find_name = [this]() -> index_t {
      std::string name;
      printf("Name: "), std::cin >> name;
      return db.find_username(name);
    };

    auto find_number = [this]() -> index_t {
      size_t number;
      printf("Number: "), check_cin(number);
      return db.find_number(number);
    };

    auto find_score = [this]() -> std::vector<index_t> {
      size_t score;
      printf("Score: "), check_cin(score);
      return db.find_score(score);
    };

    int key{};
    check_cin(key);
    CLEAR();

    switch (key) {
    case 1:
      key = find_name();
      break;
    case 2:
      key = find_number();
      break;
    case 3: {
      auto t = find_score();
      if (t.size() == 1)
        key = t[0];
      else if (t.size() > 1) {
        for (auto _ : t)
          db.print_user(_);
        PAUSE();
        continue;
      } else
        key = -1;
      break;
    }
    case 0:
      lock = finished;
      continue;
    default:
      continue;
    }

    if (key == -1) {
      printf("User not found :(\n"), SLEEP(1);
      continue;
    }

    admin_submenu_manage(key);
  }
}

void session::admin_submenu_manage(index_t index) {
  status lock{};
  menu m(manage_user);

  while (lock == running) {
    m.show();

    auto modify = [index, this]() {
      printf("Original information of this student:\n");
      scores_list_header();
      db.print_user(index);
      db.erase(index);
      printf(SGR_WHITE_FOREGROUND SGR_UNDERLINE_OFF "\n");
      printf("Insert the new information of this student:\n");
      db.add_user(student);
    };

    auto earse = [index, this]() { db.erase(index); };

    int key{};
    check_cin(key);
    CLEAR();

    switch (key) {
    case 1:
      scores_list_header();
      db.print_user(index);
      PAUSE();
      break;
    case 2:
      modify(), uindex_gen();
      index = db.size() - 1;
      break;
    case 3:
      earse(), uindex_gen();
      lock = finished;
      continue;
    case 0:
      lock = finished;
      continue;
    default:
      continue;
    }
  }
}
