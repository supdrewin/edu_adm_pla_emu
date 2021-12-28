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

# statically linked binaries are not supported on Mac OS X
ifeq ($(shell uname -a |grep Darwin), )
  LDFLAGS += -static
endif
