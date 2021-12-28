#pragma once

#include <cstdlib>

#if defined(_WIN32)
#define CLEAR() system("cls")
#define PAUSE() system("pause")
#include <windows.h>
#define SLEEP(sec) Sleep(sec * 1000)
#else // !defined(_WIN32)
#define CLEAR() system("clear")
#define PAUSE() system("bash -c 'read -n 1'")
#include <unistd.h>
#define SLEEP(sec) sleep(sec)
#endif // defined(_WIN32)
