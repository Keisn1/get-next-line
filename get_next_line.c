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

char	*add_to_return(char buf[BUFFER_SIZE], int bytes_read, bool first_read)
{
	static char	*ret = NULL;
	char		*new;
	int			size;
	int			size_ret;

	if (first_read) {
		if (ret)
			free(ret);
		ret = NULL;
	}
	size_ret = 0;
	if (ret)
		size_ret = ft_strlen(ret);
	size = size_ret + bytes_read + 1;
	new = ft_get_empty_str(size);
	ft_memcpy(new, ret, size_ret);
	ft_memcpy(new+size_ret, buf, bytes_read);
	new[size_ret+bytes_read] = '\0';
	if (ret)
		free(ret);
	ret = new;
	return (ret);
}

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	int		bytes_read;
	char	*ret;
	bool first_read;

	ret = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	first_read = true;

	while (bytes_read > 0)
	{
		ret = add_to_return(buffer, bytes_read, first_read);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		first_read = false;
	}

	return (ret);
}
