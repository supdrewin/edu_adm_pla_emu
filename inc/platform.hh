#pragma once

#include <cstdlib>

#if defined(__unix__)
#define __clear() system("clear")
#include <unistd.h>
#define __sleep(sec) sleep(sec)
#elif defined(_WIN32)
#define __clear() system("cls")
#include <windows.h>
#define __sleep(sec) sleep(sec * 1000)
#endif
