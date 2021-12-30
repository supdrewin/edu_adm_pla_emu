#include "session.hpp"

void session::scores_list_header() {
  printf(SGR_BOLD SGR_GREEN_FOREGROUND SGR_UNDERLINE_ON);

  size_t count{db.its.size() * 11 + 12};
  if (cur_user.id == teacher)
    count += 25;
  while (count--)
    printf(" ");

  printf("\n|");
  if (cur_user.id == teacher)
    printf("  student  |   number   |");
  printf("    all   |");
  for (auto _ : db.its)
    printf("%8s  |", _.c_str());
  printf(SGR_MAGENTA_FOREGROUND "\n");

  cur_user.id == student ? printf("|") : 0;
}

void session::print() {
  printf(SGR_BLACK_BACKGROUND SGR_WHITE_FOREGROUND "\n"), CLEAR();
  scores_list_header();

  if (not cur_user.id) {
    for (size_t i{}; i < db.size(); ++i)
      if (db[i].user.id)
        db.print_user(i);
    PAUSE();
    return;
  }

  db.print_scores(uindex), PAUSE();
}
