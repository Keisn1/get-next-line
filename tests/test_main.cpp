#include "test_get_next_line.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);

    // ::testing::GTEST_FLAG(filter) = "ReadingStdinTest.TestGetNextLine";
	return RUN_ALL_TESTS();
}
