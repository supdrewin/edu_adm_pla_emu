SHELL = /bin/bash

override Project = TODO
override workspaceFolder = $(PWD)
export workspaceFolder

all:
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean
PHONY: clean
