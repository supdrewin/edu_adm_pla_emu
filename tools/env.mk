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

LDFLAGS += \
	-static
