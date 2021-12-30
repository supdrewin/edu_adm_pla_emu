#pragma once

#include <string>
#include <vector>

namespace en_US {

static const std::vector<std::string> menu_main{
    "Add a student",          "Find a student",    "Add an exam subject",
    "Delete an exam subject", "Sort the database", "Show the database",
    "Sync the database",      "Account settings",  "Logout this user",
    "Exit program",
};

static const std::vector<std::string> menu_sort{
    "Sort by name",
    "Sort by number",
    "Sort by score",
    "Up to previous",
};

static const std::vector<std::string> menu_find{
    "Find student name",
    "Find student number",
    "Find student score",
    "Up to previous",
};

static const std::vector<std::string> menu_user{
    "Show my scores",
    "Account settings",
    "Logout this user",
    "Exit program",
};

static const std::vector<std::string> settings{
    "Change my password",
    "Up to previous",
};

static const std::vector<std::string> manage_user{
    "Show user infomation",
    "Modify user infomation",
    "Delete this user",
    "Up to previous",
};

} // namespace en_US
