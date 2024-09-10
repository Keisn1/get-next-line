#include "../get_next_line.h"
#include <stdio.h>

int main() {
	char *line;
	line = get_next_line(fileno(stdin));
	while (line) {
		printf("%s", line);
		free(line);
		line = get_next_line(fileno(stdin));
	}

	return 0;
}
