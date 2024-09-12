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

size_t	ft_strlen(const char *s)
{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

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
	char	*cur_stash;
	char	*ret;
	size_t	count;

	cur_stash = crud_stash(GET_STASH, "");
	count = 0;
	if (!cur_stash)
		return (cur_stash);
	while (count < ft_strlen(cur_stash))
	{
		if (cur_stash[count++] == '\n')
		{
			ret = ft_substr(cur_stash, 0, count);
			if (count == ft_strlen(cur_stash))
				crud_stash(DELETE_STASH, "");
			else
				crud_stash(SET_STASH, cur_stash + count);
			free(cur_stash);
			return (ret);
		}
	}
	crud_stash(DELETE_STASH, "");
	return (cur_stash);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	long int	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		crud_stash(UPDATE_STASH, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	buffer = NULL;
	if (bytes_read < 0)
		return (crud_stash(DELETE_STASH, NULL));
	return (truncate_stash());
}
