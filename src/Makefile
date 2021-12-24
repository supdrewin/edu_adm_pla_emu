OBJS := \
	main.o

main.elf: $(OBJS)
	$(LINK.cc) -o $@ $^

clean:
	$(RM) $(OBJS) a.out
.PHONY: clean

-include $(workspaceFolder)/tools/env.mk

