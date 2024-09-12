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
	int fd = open("test_files/nl", O_RDONLY);
	int count = 0;
	line = get_next_line(fd);
	printf("%d: %s\n",count, line);
	count++;
	while (line) {
		free(line);
		line = get_next_line(fd);
		printf("%d: %s\n",count, line);
		count++;
	}

	return 0;
}
