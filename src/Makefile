CC = gcc
CFLAGS = -c -Wall -Werror -fpic
CROSS_COMPILE = arm-linux-gnueabihf-
PREFIX ?= arm-
DIRS = $(patsubst ./%/,%,$(wildcard ./*/))
TOOLS = $(basename $(filter %.c, $(wildcard ./*/*)))
OBJ = $(foreach tool,$(addsuffix .so,$(TOOLS)),$(addprefix $(addsuffix lib,$(dir $(tool))),$(notdir $(tool))))
LIB_FLAGS = $(foreach tool,$(notdir $(TOOLS)), $(addsuffix $(tool),-L -l))

.PHONY: all clean

all: $(PREFIX)busybox

$(PREFIX)busybox: $(OBJ) main.c
	$(CROSS_COMPILE)$(CC) $(LIB_FLAGS) -Wall -o $@

%.o: %.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $< -o $@

lib%.so: %.o
	$(CROSS_COMPILE)$(CC) -shared $< -o $@

clean:
	rm -f **/*.o **/*.so $(PREFIX)busybox
