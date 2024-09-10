#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

/* int main() { */
/* 	char *line; */
/* 	line = get_next_line(fileno(stdin)); */
/* 	while (line) { */
/* 		printf("%s", line); */
/* 		free(line); */
/* 		line = get_next_line(fileno(stdin)); */
/* 	} */

/* 	return 0; */
/* } */

int main() {
	char *line;
	int fd = open("test_files/4", O_RDONLY);
	line = get_next_line(fd);
	while (line) {
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}

	return 0;
}
