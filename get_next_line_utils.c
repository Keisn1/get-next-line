/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:50/49 by kfreyer           #+#    #+#             */
/*   Updated: 2024/09/09 17:50:49 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*res_o;
	char	*res;
	int		len;

	if (!s)
		return NULL;
	len = ft_strlen(s);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return NULL;
	res_o = res;
	while (*s)
		*res++ = *s++;
	*res = '\0';
	return (res_o);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		dlen;
	size_t		n;

	n = size;
	d = dst;
	while (*d && n-- != 0)
		d++;
	dlen = d - dst;
	n = size - dlen;
	if (n == 0)
		return (ft_strlen(src) + dlen);
	s = src;
	while (*s)
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (dlen + (s - src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	size;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = (char *)malloc((size) * sizeof(char));
	if (!res)
		return (NULL);
	*res = '\0';
	ft_strlcat(res, s1, size);
	ft_strlcat(res, s2, size);
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	count;
	char	*new;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
	{
		new = (char *)malloc(1);
		if (!new)
			return (NULL);
		*new = '\0';
		return (new);
	}
	if ((len_s - start) < len)
		len = len_s - start;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	count = 0;
	while (count < len)
		new[count++] = s[start++];
	new[count] = '\0';
	return (new);
}
