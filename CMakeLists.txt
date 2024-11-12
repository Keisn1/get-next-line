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
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

file(GLOB SRC_FILES "src/*.c")
file(GLOB TEST_FILES "tests/*.cpp")

# Handle BUFFER_SIZE values
set(BUFFER_SIZES 1 2 3 4 8 16 32 64 9999)
if(DEFINED BUFFER_SIZE AND NOT BUFFER_SIZE STREQUAL "")
  set(BUFFER_SIZES ${BUFFER_SIZE})
  message("buffer size is set to ${BUFFER_SIZE}, testing BUFFER_SIZES = ${BUFFER_SIZES}")
else()
  message("buffer size is not set, testing sizes: BUFFER_SIZES = ${BUFFER_SIZES}")
endif()

foreach(SIZE IN LISTS BUFFER_SIZES)
  set(TEST_NAME "run_tests_bs_${SIZE}")
  add_executable(${TEST_NAME} ${SRC_FILES} ${TEST_FILES})

  target_compile_definitions(${TEST_NAME} PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test_files/")
  target_compile_definitions(${TEST_NAME} PRIVATE BUFFER_SIZE=${SIZE})

  target_include_directories(${TEST_NAME} PRIVATE includes)
  target_include_directories(${TEST_NAME} PRIVATE ${gtest_SOURCE_DIR}/googletest/include)

  target_link_libraries(
    ${TEST_NAME}
    GTest::gtest
    GTest::gtest_main
    pthread
  )

  # Register the test with CTest
  include(GoogleTest)
  gtest_discover_tests(${TEST_NAME})
endforeach()
