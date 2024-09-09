##
# get_next_line
#
# @file
# @version 0.1

CC := cc
CFLAGS := -Wall -Werror -Wextra -D BUFFER_SIZE=64

CXX := g++
CXX_FLAGS := -Wall -Werror -Wextra
FSANITIZE := -fsanitize=address
LDFLAGS := -lgtest -lgtest_main -pthread #for googletests

SRC_DIR := .
OBJ_DIR := .

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_TARGET := run_test

all: $(OBJ_FILES)

$(TEST_TARGET): $(OBJ_FILES) test.cpp
	$(CXX) $(FSANITIZE) -o run_test test.cpp $(OBJ_FILES) $(LDFLAGS)

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(TEST_TARGET)

re: fclean all

test: $(TEST_TARGET)
	- ./run_test

bear:

norm:
	norminette -R CheckForbiddenSourceHeader -R CheckDefine

.PHONY: norm clean

print_src_files:
	@echo $(SRC_FILES)

print_obj_files:
	@echo $(OBJ_FILES)
# end
