#include "get_next_line.h"
#include <cstdio>
#include <fcntl.h>
#include <gtest/gtest.h>


struct ReadingFileTestParams {
	std::string testfile;
	std::vector<std::string> want_strs;
	int want_times_loop;
};

class ReadingFileTest : public testing::TestWithParam<ReadingFileTestParams> {};

INSTANTIATE_TEST_SUITE_P(
	ReadingFileTests,
	ReadingFileTest,
	testing::Values(
		// ReadingFileTestParams{"./test_files/6", std::vector<std::string>{""}},
		// ReadingFileTestParams{"./test_files/5", std::vector<std::string>{"line one", "line two with newline", ""}},
		// ReadingFileTestParams{"./test_files/4", std::vector<std::string>{"line one", "line two wo newline"}},
		ReadingFileTestParams{"./test_files/3", std::vector<std::string>{"with newline at the end\n", ""}, 2},
		ReadingFileTestParams{"./test_files/2", std::vector<std::string>{"other line"}, 1},
		ReadingFileTestParams{"./test_files/1", std::vector<std::string>{"a line"}, 1},
		ReadingFileTestParams{"./test_files/0", std::vector<std::string>{}, 0}
		)
);

TEST_P(ReadingFileTest, VariousContents) {
	auto param = GetParam();
	int want_times_loop = param.want_times_loop;
	std::string filename = param.testfile;
	std::vector<std::string> want_strs = param.want_strs;

	int fd = open(filename.c_str(), O_RDONLY);

	int i = 0;
	char* got = get_next_line(fd);
	if (want_strs.size())
		ASSERT_STRNE(got, NULL);

	int got_times_loop = 0;
	while (got) {
		std::string want_str = want_strs[i];
		EXPECT_STREQ(want_str.c_str(), got);
		got = get_next_line(fd);
		i++;
		got_times_loop++;
	}

	EXPECT_EQ(NULL, got);
	free(got);

	EXPECT_EQ(want_times_loop, got_times_loop);
	close(fd);
}