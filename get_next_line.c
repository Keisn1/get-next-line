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

char	*crud_stash(t_op op, char *new_stash)
{
	static char	*stash = NULL;
	char		*tmp;

	if (op == SET_STASH)
	{
		free(stash);
		stash = ft_strdup(new_stash);
	}
	if (op == DELETE_STASH)
	{
		free(stash);
		stash = NULL;
	}
	if (op == UPDATE_STASH)
	{
		tmp = ft_strjoin(stash, new_stash);
		free(stash);
		stash = tmp;
	}
	if (op == GET_STASH)
		if (stash)
			return (ft_strdup(stash));
	return (NULL);
}

char	*truncate_stash(void)
{
	char	*stash;
	size_t	count;
	char	*ret;

	stash = crud_stash(GET_STASH, "");
	count = 0;
	if (!stash)
		return (stash);
	while (count < ft_strlen(stash))
	{
		if (stash[count++] == '\n')
		{
			if (count == ft_strlen(stash))
				crud_stash(DELETE_STASH, "");
			else
				crud_stash(SET_STASH, stash + count);
			ret = ft_get_empty_str(count + 1);
			ft_memcpy(ret, stash, count);
			ret[count] = '\0';
			free(stash);
			return (ret);
		}
	}
	crud_stash(DELETE_STASH, "");
	return (stash);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	long int	bytes_read;
	char		*ret;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		crud_stash(UPDATE_STASH, buffer);
		if (ft_strchr(buffer, '\n'))
			break;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	buffer = NULL;
	if (bytes_read < 0)
		return (crud_stash(DELETE_STASH, ""));
	ret = truncate_stash();
	return (ret);
}
