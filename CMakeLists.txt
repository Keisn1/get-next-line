cmake_minimum_required(VERSION 3.14)
project(get_next_line)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

# Create the test executable
file(GLOB SRC_FILES "src/*.c")
file(GLOB TEST_FILES "tests/*.cpp")
add_executable(run_tests ${SRC_FILES} ${TEST_FILES})

target_compile_definitions(run_tests PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test_files/")
target_include_directories(run_tests PRIVATE includes)
target_include_directories(run_tests PRIVATE ${gtest_SOURCE_DIR}/googletest/include)

# Link the test executable with GoogleTest and your static library
target_link_libraries(
  run_tests
  GTest::gtest
  GTest::gtest_main
  pthread
)

include(GoogleTest)
gtest_discover_tests(run_tests)
