CC = gcc
CC_FLAGS = -Wall -O3
LN_FLAGS = -lm

INCLUDES = -I includes/

SRC_FILES = $(wildcard src/*.c) $(wildcard test/*.c)
OBJ_FILES = $(addprefix bin/,$(notdir $(SRC_FILES:.c=.o)))
DEP_FILES = $(OBJ_FILES:.o=.d)

BIN = ./bin/test

all: $(BIN)

$(BIN): $(OBJ_FILES)
	$(CC) $(LN_FLAGS) $^ -o $@
-include $(DEP_FILES)


bin/%.o: test/%.c
	$(CC) $(CC_FLAGS) $(INCLUDES) -MMD -c $< -o $@

bin/%.o: src/%.c
	$(CC) $(CC_FLAGS) $(INCLUDES) -MMD -c $< -o $@

clean:
	-rm ./bin/*
