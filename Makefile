##
# get_next_line
#
# @file
# @version 0.1

CC := cc
CFLAGS := -Wall -Werror -Wextra
INCLUDES := -Iincludes

CXX := g++
FSANITIZE := -fsanitize=address

BUFFER_FLAG := -DBUFFER_SIZE
BUFFER_SIZE := 16

SRC_DIR := src
OBJ_DIR := obj

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME := your_echo

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) -g $(CFLAGS) $(FSANITIZE) $(BUFFER_FLAG)$(BUFFER_SIZE) -o $(NAME) ./example/main.c $(OBJ_FILES) $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(BUFFER_FLAG)$(BUFFER_SIZE) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -rf build
	rm -f $(NAME)

re: fclean all

test:
	- cmake -S . -B build -DBUFFER_SIZE=$(BUFFER_SIZE)
	- cmake --build build
	- cd build && ctest -V

test_all: fclean
	- cmake -S . -B build
	- cmake --build build
	- cd build && ctest -V

# build/Makefile: CMakeLists.txt $(shell find src -name '*.c') $(shell find tests -name '*.cpp' -o -name '*.cc')

norm:
	norminette -R CheckForbiddenSourceHeader -R CheckDefine

.PHONY: norm clean test

print_src_files:
	@echo $(SRC_FILES)

print_obj_files:
	@echo $(OBJ_FILES)

# end
