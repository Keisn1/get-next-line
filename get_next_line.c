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

char	*add_to_return(char buf[BUFFER_SIZE], int bytes_read)
{
	static char	*ret = "";
	char		*new;
	int			size;
	int			count1;
	int			count2;

	size = ft_strlen(ret) + bytes_read + 1;
	new = ft_get_empty_str(size);
	ft_strlcat(new, ret, size);
	count1 = 0;
	count2 = ft_strlen(ret);
	while (count1 < bytes_read)
	{
		new[count2] = buf[count1];
		count1++;
		count2++;
	}
	new[count2] = '\0';
	if (ft_strlen(ret) > 0)
		free(ret);
	ret = new;
	return (ret);
}

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	int		bytes_read;
	char	*ret;

	ret = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		ret = add_to_return(buffer, bytes_read);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}

	return (ret);
}
