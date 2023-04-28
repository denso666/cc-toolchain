CC = gcc
CFLAGS = -c -Wall -Werror -fpic
CROSS_COMPILE = arm-linux-gnueabihf-
PREFIX ?= arm-
OUTPUT_DIR ?= ../output/
DIRS = $(patsubst ./%/,%,$(wildcard ./*/))
TOOLS = $(basename $(filter %.c, $(wildcard ./*/*)))
OBJ = $(foreach tool,$(addsuffix .so,$(TOOLS)),$(addprefix $(addsuffix lib,$(dir $(tool))),$(notdir $(tool))))
LIB_FLAGS = $(foreach tool,$(notdir $(TOOLS)), $(addsuffix $(tool),-L -l))
SSH_CREDENTIALS ?= debian@192.168.7.2
BIN = $(OUTPUT_DIR)$(PREFIX)busybox

.PHONY: all clean install

all: $(OUTPUT_DIR)$(PREFIX)busybox

$(BIN): $(OBJ) main.c
	mkdir -p $(OUTPUT_DIR)
	$(CROSS_COMPILE)$(CC) main.c $(LIB_FLAGS) -Wall -o $@

%.o: %.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $< -o $@

lib%.so: %.o
	$(CROSS_COMPILE)$(CC) -shared $< -o $@

clean:
	rm -rf **/*.o **/*.so $(PREFIX)busybox $(OUTPUT_DIR)

install:
	ssh $(SSH_CREDENTIALS) 'mkdir ~/lib'
	scp $(BIN) $(SSH_CREDENTIALS):~
	scp **/*.so $(SSH_CREDENTIALS):~/lib
	ssh $(SSH_CREDENTIALS) 'cp ~/lib/* /lib/'

