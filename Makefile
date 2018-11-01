CC_FLAGS = -Wall -std=c99
LN_FLAGS = -lm
CC = gcc

# Testing
ifneq "$(findstring test, $(MAKECMDGOALS))" ""
CC_FLAGS += -O3 -MMD
SRC_FILES = $(wildcard test/test.c)
OBJ_EXTENSION = o
endif

# Native Lib
ifneq "$(findstring libnative, $(MAKECMDGOALS))" ""
CC_FLAGS += -O3 -MMD
OBJ_EXTENSION = o
endif

# emscripten
ifneq "$(findstring libjs, $(MAKECMDGOALS))" ""
CC = emcc
CC_FLAGS += -O2
OBJ_EXTENSION = bc
endif

ifeq ($(BOUNDS_CHECK), 1)
CC_FLAGS += -DBOUNDS_CHECK
endif

ifeq ($(CLANG), 1)
CC = clang
ifeq ($(SAN), mem)
CC_FLAGS += -fsanitize=memory -fno-omit-frame-pointer
LN_FLAGS += -fsanitize=memory
endif
ifeq ($(SAN), adr)
CC_FLAGS += -fsanitize=address -fno-omit-frame-pointer
LN_FLAGS += -fsanitize=address
endif
ifeq ($(SAN), und)
CC_FLAGS += -fsanitize=undefined
LN_FLAGS += -fsanitize=undefined
endif
endif

# -----------------------------------------------------------------------------

INCLUDES = -I include/

SRC_FILES += $(wildcard src/*.c)
OBJ_FILES = $(addprefix bin/,$(notdir $(SRC_FILES:.c=.$(OBJ_EXTENSION))))
DEP_FILES = $(OBJ_FILES:.$(OBJ_EXTENSION)=.d)

TEST = ./bin/test
LIB_NATIVE = ./bin/libelfc.a
LIB_JS = ./bin/libelfc_js.a

test: $(TEST)
libnative: $(LIB_NATIVE)
libjs: $(LIB_JS)
clean:
	-rm ./bin/*

$(TEST): $(OBJ_FILES)
	$(CC) $(LN_FLAGS) $^ -o $@

$(LIB_NATIVE): $(OBJ_FILES)
	ar rcs $@ $^

$(LIB_JS): $(OBJ_FILES)
	emar r $@ $^

-include $(DEP_FILES)

# -----------------------------------------------------------------------------

bin/%.$(OBJ_EXTENSION): test/%.c
	$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

bin/%.$(OBJ_EXTENSION): src/%.c
	$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@
