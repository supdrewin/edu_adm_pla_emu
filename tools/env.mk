SHELL := bash

CXXFLAGS += \
	-std=c++1z \
	-I$(workspaceFolder)/inc \
	-Wall \
	-Wextra \
	-pedantic \
	-Weffc++ \
	-pipe \
	-O2

# statically linked binaries are not supported on macOS
ifeq ($(shell uname -a |grep Darwin), )
  LDFLAGS += -static
endif
