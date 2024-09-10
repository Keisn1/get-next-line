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
#include <stdio.h>

char	*add_to_return(char buf[BUFFER_SIZE], int bytes_read, bool new_file)
{
	static char	*stash = NULL;
	char		*new;
	int			size_new;
	int			size_stash;
	int			count;
	bool found_newline;

	if (new_file)
	{
		free(stash);
		stash = NULL;
	}
	size_stash = 0;
	if (stash)
		size_stash = ft_strlen(stash);
	count = 0;
	while (count < bytes_read && buf[count] != '\n')
		count++;

	found_newline = false;
	if (count < bytes_read) {
		found_newline = true;
		count++;
	}

	size_new = size_stash + count + 1;
	new = ft_get_empty_str(size_new);
	ft_memcpy(new, stash, size_stash);
	ft_memcpy(new + size_stash, buf, count);
	new[size_stash + count] = '\0';

	if (stash)
		free(stash);

	/* if (count == BUFFER_SIZE) */
	/* if (count == bytes_read) */
	if (!found_newline)
	{
		stash = ft_get_empty_str(ft_strlen(new)+1);
		ft_memcpy(stash, new, ft_strlen(new)+1);
	}
	else
	{
		/* printf("count: %d\n", count); */
		/* printf("buffer[count]: %c\n", buf[count]); */
		stash = ft_get_empty_str(BUFFER_SIZE - count + 1);
		ft_memcpy(stash, buf + count, BUFFER_SIZE - count);
		stash[BUFFER_SIZE - count] = '\0';
		/* printf("stash: %s\n", stash); */
	}

	return (new);
}

char	*get_next_line(int fd)
{
	static int old_fd = -1;
	char	buffer[BUFFER_SIZE];
	int		bytes_read;
	char	*ret;
	bool	new_file;


	new_file = false;
	if (fd != old_fd)
		new_file = true;
	old_fd = fd;

	ret = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		if (ret)
			free(ret);
		ret = add_to_return(buffer, bytes_read, new_file);
		/* printf("here: %s\n", ret); */
		if (ret[ft_strlen(ret) - 1] == '\n')
			break;
		new_file = false;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}

	return (ret);
}
