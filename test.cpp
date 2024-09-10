#include "get_next_line.h"
#include <fcntl.h>
#include <gtest/gtest.h>


struct ReadingFileTestParams {
	std::string testfile;
	std::vector<std::string> expected;
};

class ReadingFileTest : public testing::TestWithParam<ReadingFileTestParams> {};

INSTANTIATE_TEST_SUITE_P(
	ReadingFileTests,
	ReadingFileTest,
	testing::Values(
		ReadingFileTestParams{"./test_files/1", std::vector<std::string>{"a line"}},
		ReadingFileTestParams{"./test_files/2", std::vector<std::string>{"other line"}},
		ReadingFileTestParams{"./test_files/3", std::vector<std::string>{"with newline at the end"}}
		)
);

TEST_P(ReadingFileTest, VariousContents) {
	auto param = GetParam();
	std::string filename = param.testfile;
	std::vector<std::string> strings = param.expected;
	
	int fd = open(filename.c_str(), O_RDONLY);
	
	char* got;
	for (const auto& str : strings) {
		get_next_line(fd ,&got);
		EXPECT_STREQ(str.c_str(), got);
		free(got);
	}
	close(fd);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
