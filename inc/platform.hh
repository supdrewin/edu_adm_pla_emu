#pragma once

#include <cstdlib>

#if defined(__unix__)
#define CLEAR() system("clear")
#define PAUSE() system("bash -c 'read -n 1'")
#include <unistd.h>
#define SLEEP(sec) sleep(sec)
#elif defined(_WIN32)
#define CLEAR() system("cls")
#define PAUSE() system("pause")
#include <windows.h>
#define SLEEP(sec) sleep(sec * 1000)
#endif
