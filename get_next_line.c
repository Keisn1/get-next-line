/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:37/54 by kfreyer           #+#    #+#             */
/*   Updated: 2024/09/09 17:37:54 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

int	get_next_line(int fd, char **line)
{
	char buffer[BUFFER_SIZE];
	char* cur = buffer;

    while (read(fd, cur, 1) == 1) {
		if (*cur == '\n')
			break;
		cur++;
    }
	*cur = '\0';
	printf("%d", BUFFER_SIZE);
	*line = strdup(buffer);
	return (0);
}
