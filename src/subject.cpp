#include "session.hpp"

void session::add_item() {
  std::string item;
  printf("The subject you want to add: "), std::cin >> item;
  db.add_item(item), printf("Success!!\n"), SLEEP(1);
}

void session::del_item() {
  std::string item;
  printf("The subject you want to delete: "), std::cin >> item;
  db.del_item(item) ? printf("Success!!\n") : printf("Failed!!\n");
  SLEEP(1);
}
