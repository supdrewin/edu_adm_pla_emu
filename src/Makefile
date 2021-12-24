OBJS := \
	main.o

all: $(OBJS)
	$(LINK.cc) $^

clean:
	$(RM) $(OBJS) a.out
.PHONY: clean

-include $(workspaceFolder)/tools/env.mk

