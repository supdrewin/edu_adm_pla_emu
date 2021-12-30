OBJS := \
	main.o \
	menu.o \
	admin_menu.o \
	user_menu.o \
	subject.o \
	print.o

main.run: $(OBJS)
	$(LINK.cc) -o $@ $^

clean:
	$(RM) *.{o,elf}
.PHONY: clean

-include $(workspaceFolder)/tools/env.mk
