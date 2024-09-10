#include "get_next_line.h"
#include <stdio.h>

int main() {
	char *line;
	while (get_next_line(fileno(stdin), &line) != 0)
		printf("%s here", line);

	return 0;
}
