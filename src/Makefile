OBJS := \
	main.o

main.elf: $(OBJS)
	$(LINK.cc) -o $@ $^

clean:
	$(RM) *.{o,elf}
.PHONY: clean

-include $(workspaceFolder)/tools/env.mk
