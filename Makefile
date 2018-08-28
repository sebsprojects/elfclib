CC = gcc
CC_FLAGS = -Wall -O3
LN_FLAGS = -lm

# Testing
ifneq "$(findstring test, $(MAKECMDGOALS))" ""
CC_FLAGS = -Wall -O3 -DBOUNDS_CHECK
LN_FLAGS = -lm
SRC_FILES = $(wildcard test/test.c)
endif

INCLUDES = -I includes/

SRC_FILES += $(wildcard src/*.c)
OBJ_FILES = $(addprefix bin/,$(notdir $(SRC_FILES:.c=.o)))
DEP_FILES = $(OBJ_FILES:.o=.d)

TEST = ./bin/test

test: $(TEST)

$(TEST): $(OBJ_FILES)
	$(CC) $(LN_FLAGS) $^ -o $@
-include $(DEP_FILES)


bin/%.o: test/%.c
	$(CC) $(CC_FLAGS) $(INCLUDES) -MMD -c $< -o $@

bin/%.o: src/%.c
	$(CC) $(CC_FLAGS) $(INCLUDES) -MMD -c $< -o $@

clean:
	-rm ./bin/*
