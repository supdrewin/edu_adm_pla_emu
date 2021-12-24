SHELL := bash

CXXFLAGS += \
	-I$(workspaceFolder)/inc \
	-Wall \
	-Wextra \
	-pedantic \
	-Weffc++
