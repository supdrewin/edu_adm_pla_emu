#pragma once

#include <string>
#include <vector>

namespace en_US {

static const std::vector<std::string> menu_main{
    "Add a student",          "Find a student",    "Add an exam subject",
    "Delete an exam subject", "Show the database", "Sync the database",
    "Account settings",       "Logout this user",  "Exit program",
};

static const std::vector<std::string> menu_find{
    "Find student name",
    "Find student number",
    "Find student score",
    "Return to main menu",
};

static const std::vector<std::string> menu_user{
    "Show my scores",
    "Account settings",
    "Logout this user",
    "Exit program",
};

static const std::vector<std::string> settings{
    "Change my password",
    "Return to main menu",
};

static const std::vector<std::string> manage_user{
    "Show user infomation",
    "Modify user infomation",
    "Delete this user",
    "Cancel and Return",
};

} // namespace en_US
