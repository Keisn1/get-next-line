#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

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
	int fd = open("test_files/4test", O_RDONLY);
	int count = 0;
	line = get_next_line(fd);
	printf("%d: %s",count, line);
	count++;
	while (line) {
		free(line);
		line = get_next_line(fd);
		printf("%d: %s\n",count, line);
		count++;
	}

	return 0;
}
