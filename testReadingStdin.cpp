// #include "get_next_line.h"
// #include <gtest/gtest.h>

// class ReadingStdinTest : public ::testing::Test {
// protected:
// 	void SetUp() override {
// 		tmpfile = std::tmpfile();
// 		// Write your test input to the temporary file
// 		std::fprintf(tmpfile, "Test input\n");
// 		// Rewind the file to the beginning
// 		std::rewind(tmpfile);

// 		// Redirect stdin to the temporary file
// 		int fd = fileno(tmpfile);
// 		freopen(nullptr, "r", stdin);
// 		dup2(fd, fileno(stdin));
// 	}

// 	void TearDown() override {
// 		std::fclose(tmpfile);
// 	}

// 	FILE* tmpfile;
// };

// TEST_F(ReadingStdinTest, TestGetNextLine) {
    // char* line = nullptr;
    // line = get_next_line(fileno(stdin));

	// EXPECT_STREQ("Test input", line);
	// free(line);
// }
