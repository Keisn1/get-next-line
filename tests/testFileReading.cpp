#include "test_get_next_line.hpp"


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
		ReadingFileTestParams{"5", std::vector<std::string>{"line one\n", "line two with newline\n"}, 2},
		ReadingFileTestParams{"4", std::vector<std::string>{"line one\n", "line two wo newline"}, 2},
		ReadingFileTestParams{"16charLine", std::vector<std::string>{"161616161616161\n"}, 1},
		ReadingFileTestParams{"3", std::vector<std::string>{"with newline at the end\n"}, 1},
		ReadingFileTestParams{"2", std::vector<std::string>{"other line"}, 1},
		ReadingFileTestParams{"nl", std::vector<std::string>{"\n", ""}, 1},
		ReadingFileTestParams{"4", std::vector<std::string>{"line one\n", "line two wo newline"}, 2},
		ReadingFileTestParams{"1", std::vector<std::string>{"a line"}, 1},
		ReadingFileTestParams{"0", std::vector<std::string>{}, 0}
		)
);

TEST_P(ReadingFileTest, VariousContents) {
	auto param = GetParam();
	int want_times_loop = param.want_times_loop;

	const std::string testDataDir = TEST_DATA_DIR;
	std::string filename = testDataDir + param.testfile;
	std::vector<std::string> want_strs = param.want_strs;

	int fd = open(filename.c_str(), O_RDONLY);
	ASSERT_NE(-1, fd);

	char* got = get_next_line(fd);
	if (want_strs.size())
		ASSERT_STRNE(got, NULL);

	int i = 0;
	int got_times_loop = 0;
	while (got) {
		std::string want_str = want_strs[i];
		EXPECT_STREQ(want_str.c_str(), got);
		free(got);
		got = get_next_line(fd);
		i++;
		got_times_loop++;
	}

	EXPECT_EQ(NULL, got);
	free(got);

	EXPECT_EQ(want_times_loop, got_times_loop);
	close(fd);
}


TEST(ReadingFileTest, wrongFile) {
	char* got  = get_next_line(1000);
	EXPECT_EQ(NULL, got);
}
