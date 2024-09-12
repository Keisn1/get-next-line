##
# get_next_line
#
# @file
# @version 0.1

CC := cc
CFLAGS := -Wall -Werror -Wextra
BUFFER_FLAG = -D BUFFER_SIZE=
BUFFER_SIZE = 16

CXX := g++
CXX_FLAGS := -Wall -Werror -Wextra
FSANITIZE := -fsanitize=address
LDFLAGS := -lgtest -lgtest_main -pthread #for googletests

SRC_DIR := .
OBJ_DIR := .

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_FILES := $(wildcard $(SRC_DIR)/*.cpp)
TEST_TARGET := run_test

NAME := your_echo

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) -g $(CFLAGS) $(FSANITIZE) $(BUFFER_FLAG)$(BUFFER_SIZE) -o $(NAME) ./example/main.c $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -g $(CFLAGS) $(BUFFER_FLAG)$(BUFFER_SIZE) -c $(SRC_FILES)

$(TEST_TARGET): $(OBJ_FILES) $(TEST_FILES)
	$(CXX) $(FSANITIZE) -o run_test $(TEST_FILES) $(OBJ_FILES) $(LDFLAGS)

clean:
	rm -f $(OBJ_FILES)
	rm -f $(TEST_TARGET)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: fclean $(TEST_TARGET)
	- ./run_test

bear:

norm:
	norminette -R CheckForbiddenSourceHeader -R CheckDefine

.PHONY: norm clean test

print_src_files:
	@echo $(SRC_FILES)

print_obj_files:
	@echo $(OBJ_FILES)
# end
