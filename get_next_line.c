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

char	*add_to_return(char buf[BUFFER_SIZE], int bytes_read, bool first_read)
{
	static char	*stash = NULL;
	char		*new;
	int			size;
	int			size_stash;
	int			count;

	if (first_read)
	{
		/* printf("\n\n here: %s \n\n", stash); */
		if (stash)
			free(stash);
		stash = NULL;
	}
	size_stash = 0;
	if (stash)
		size_stash = ft_strlen(stash);
	count = 0;
	while (count < bytes_read && buf[count] != '\n')
	{
		count++;
	}
	if (buf[count] == '\n')
		count++;
	size = size_stash + count + 1;
	/* size = size_ret + bytes_read + 1; */
	new = ft_get_empty_str(size);
	ft_memcpy(new, stash, size_stash);
	ft_memcpy(new + size_stash, buf, count);
	/* ft_memcpy(new+size_ret, buf, bytes_read); */
	new[size_stash + count] = '\0';
	/* new[size_ret+bytes_read] = '\0'; */
	if (stash)
		free(stash);
	if (count == BUFFER_SIZE)
	{
		stash = ft_get_empty_str(ft_strlen(new));
		ft_memcpy(stash, new, ft_strlen(new));
	}
	else
	{
		stash = ft_get_empty_str(BUFFER_SIZE - count);
		ft_memcpy(stash, buf + count, BUFFER_SIZE - count);
	}
	return (new);
}

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	int		bytes_read;
	char	*ret;
	bool	first_read;

	ret = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	first_read = true;
	while (bytes_read > 0)
	{
		if (ret)
			free(ret);
		ret = add_to_return(buffer, bytes_read, first_read);
		first_read = false;
		if (ret[ft_strlen(ret) - 1] == '\n')
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}

	return (ret);
}
