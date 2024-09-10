#include "get_next_line.h"
#include <cstdio>
#include <fcntl.h>
#include <gtest/gtest.h>


struct ReadingFileTestParams {
	std::string testfile;
	std::vector<std::string> want_strs;
	std::vector<int> want_vals;
};

class ReadingFileTest : public testing::TestWithParam<ReadingFileTestParams> {};

INSTANTIATE_TEST_SUITE_P(
	ReadingFileTests,
	ReadingFileTest,
	testing::Values(
		ReadingFileTestParams{"./test_files/6", std::vector<std::string>{""},std::vector<int>{0}},
		ReadingFileTestParams{"./test_files/5", std::vector<std::string>{"line one", "line two with newline", ""},std::vector<int>{1, 1, 0}},
		ReadingFileTestParams{"./test_files/4", std::vector<std::string>{"line one", "line two wo newline"}, std::vector<int>{1, 0}},
		ReadingFileTestParams{"./test_files/3", std::vector<std::string>{"with newline at the end", ""}, std::vector<int>{1, 0}},
		ReadingFileTestParams{"./test_files/2", std::vector<std::string>{"other line"},std::vector<int>{0}},
		ReadingFileTestParams{"./test_files/1", std::vector<std::string>{"a line"}, std::vector<int>{0}}
		)
);

TEST_P(ReadingFileTest, VariousContents) {
	auto param = GetParam();
	std::string filename = param.testfile;
	std::vector<std::string> want_strs = param.want_strs;
	std::vector<int> want_vals = param.want_vals;

	int fd = open(filename.c_str(), O_RDONLY);

	char* got;

	for (size_t i = 0; i < want_strs.size(); ++i) {
		std::string want_str = want_strs[i];
		int want_val = want_vals[i];

		int got_val = get_next_line(fd ,&got);
		EXPECT_STREQ(want_str.c_str(), got);
		EXPECT_EQ(want_val, got_val);
		free(got);
	}
	close(fd);
}
