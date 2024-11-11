##
# get_next_line
#
# @file
# @version 0.1

CC := cc
CFLAGS := -Wall -Werror -Wextra
INCLUDES := -Iincludes

BUFFER_FLAG = -D BUFFER_SIZE=
BUFFER_SIZE = 16

CXX := g++
FSANITIZE := -fsanitize=address
GTEST := -Lgtest -lgtest -lgtest_main -pthread #for googletests

SRC_DIR := src
OBJ_DIR := obj
TEST_DIR := tests

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
TEST_SRC_FILES := $(wildcard $(TEST_DIR)/*.cpp)

OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_OBJ_FILES := $(TEST_SRC_FILES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TEST_TARGET := run_test
NAME := your_echo

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) -g $(CFLAGS) $(FSANITIZE) $(BUFFER_FLAG)$(BUFFER_SIZE) -o $(NAME) ./example/main.c $(OBJ_FILES) $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(BUFFER_FLAG)$(BUFFER_SIZE) $(INCLUDES) -c $< -o $@


$(TEST_TARGET): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CXX) $(C_FLAGS) $(FSANITIZE) -o $@ $^ $(GTEST)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(C_FLAGS) $(FSANITIZE) -c $< -o $@ $(GTEST) $(INCLUDES)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ_FILES)
	rm -f $(TEST_TARGET)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: fclean $(TEST_TARGET)
	- ./run_test

bear: all $(TEST_TARGET)

norm:
	norminette -R CheckForbiddenSourceHeader -R CheckDefine

.PHONY: norm clean test

print_src_files:
	@echo $(SRC_FILES)

print_obj_files:
	@echo $(OBJ_FILES)

print_test_files:
	@echo $(TEST_SRC_FILES)

print_test_obj_files:
	@echo $(TEST_OBJ_FILES)
# end
