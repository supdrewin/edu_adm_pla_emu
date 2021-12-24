SHELL = /bin/bash

override Project = TODO
override workspaceFolder = $(PWD)

all:
	$(MAKE) -C src workspaceFolder=$(workspaceFolder)

clean:
	$(MAKE) -C src clean
PHONY: clean
