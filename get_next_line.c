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

char	*buffer_to_string(char buffer[BUFFER_SIZE], int bytes_read)
{
	char	*ret;

	ret = (char *)malloc(bytes_read + 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, buffer, bytes_read);
	ret[bytes_read] = '\0';
	return (ret);
}

bool	check_newline_buf_str(char	*buf_str)
{
	size_t	count;

	if (!buf_str)
		return (false);
	count = 0;
	while (count < ft_strlen(buf_str))
	{
		if (buf_str[count] == '\n')
			return (true);
		count++;
	}
	return (false);
}

bool	check_newline(void)
{
	char	*stash;
	size_t	count;

	stash = crud_stash(GET_STASH, "");
	if (!stash)
		return (false);
	count = 0;
	while (count < ft_strlen(stash))
	{
		if (stash[count] == '\n')
		{
			free(stash);
			return (true);
		}
		count++;
	}
	free(stash);
	return (false);
}

char	*check_newline_and_update(void)
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


char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	long int		bytes_read;
	char	*ret;
	char	*buf_string;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf_string = buffer_to_string(buffer, bytes_read);
		if (!buf_string)
			return (NULL);
		crud_stash(UPDATE_STASH, buf_string);
		if (check_newline_buf_str(buf_string)) {
			free(buf_string);
			break ;
		}
		free(buf_string);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (NULL);
	ret = check_newline_and_update();
	return (ret);
}

