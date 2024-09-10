#include "get_next_line.h"
#include <cstdio>
#include <fcntl.h>
#include <gtest/gtest.h>


struct ReadingFileTestParams {
	std::string testfile;
	std::vector<std::string> want_strs;
};

class ReadingFileTest : public testing::TestWithParam<ReadingFileTestParams> {};

INSTANTIATE_TEST_SUITE_P(
	ReadingFileTests,
	ReadingFileTest,
	testing::Values(
		ReadingFileTestParams{"./test_files/6", std::vector<std::string>{""}},
		ReadingFileTestParams{"./test_files/5", std::vector<std::string>{"line one", "line two with newline", ""}},
		ReadingFileTestParams{"./test_files/4", std::vector<std::string>{"line one", "line two wo newline"}},
		ReadingFileTestParams{"./test_files/3", std::vector<std::string>{"with newline at the end", ""}},
		ReadingFileTestParams{"./test_files/2", std::vector<std::string>{"other line"}},
		ReadingFileTestParams{"./test_files/1", std::vector<std::string>{"a line"}}
		)
);

TEST_P(ReadingFileTest, VariousContents) {
	auto param = GetParam();
	std::string filename = param.testfile;
	std::vector<std::string> want_strs = param.want_strs;

	int fd = open(filename.c_str(), O_RDONLY);

	int i = 0;
	char* got = get_next_line(fd);
	while (got) {
		std::string want_str = want_strs[i];
		EXPECT_STREQ(want_str.c_str(), got);
		free(got);
		got = get_next_line(fd);
		i++;
	}
	free(got);

	close(fd);
}
