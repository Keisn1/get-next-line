#include "get_next_line.h"
#include <fcntl.h>
#include <gtest/gtest.h>


struct ReadingFileParameters {
	std::string testfile;
	std::vector<std::string> expected;
};

class ReadingFileTest : public testing::TestWithParam<ReadingFileParameters> {};

INSTANTIATE_TEST_SUITE_P(ReadingFileTests, ReadingFileTest,
						 testing::Values(
							 ReadingFileParameters{"./test_files/1", std::vector<std::string>{"a line"}},
							 ReadingFileParameters{"./test_files/2", std::vector<std::string>{"other line"}},
							 ReadingFileParameters{"./test_files/3", std::vector<std::string>{"with newline at the end"}}
							 // ReadingFileParameters{"./test_files/3", std::vector<std::string>{"first line", "second line"}}
							 // Add more test parameter combinations here
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
