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
	int			count1;
	int			count2;

	if (first_read) {
		if (ret)
			free(ret);
		ret = NULL;
	}
	count1 = 0;
	count2 = 0;
	if (ret)
		count2 = ft_strlen(ret);
	size = count2 + bytes_read + 1;
	new = ft_get_empty_str(size);
	if (ret)
		ft_strlcat(new, ret, size);
	while (count1 < bytes_read)
	{
		new[count2] = buf[count1];
		count1++;
		count2++;
	}
	new[count2] = '\0';
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
