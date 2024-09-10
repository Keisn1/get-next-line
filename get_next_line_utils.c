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

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*ft_strdup(const char *s)
{
	char	*res_o;
	char	*res;
	int		len;

	len = ft_strlen(s);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (res);
	res_o = res;
	while (*s)
		*res++ = *s++;
	*res = '\0';
	return (res_o);
}

char	*ft_get_empty_str(size_t n)
{
	char	*ret;

	ret = (char *)malloc(n);
	if (ret == NULL || n == 0)
		return (NULL);
	*ret = '\0';
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	count;

	if (size == 0)
		return (ft_strlen(src));
	count = 0;
	while (src[count] != '\0' && (count < size - 1))
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
	return (ft_strlen(src));
}

/*
   Appends src to string dst of size siz (unlike strncat, siz is the
   full size of dst, not space left).  At most siz-1 characters
   will be copied.  Always NUL terminates (unless siz <= strlen(dst)).
   Returns strlen(src) + MIN(siz, strlen(initial dst)).
   If retval >= siz, truncation occurred.
*/

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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			idx;

	if (!dest && !src)
		return (dest);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	idx = 0;
	while (idx < n)
	{
		d[idx] = s[idx];
		idx++;
	}
	return (dest);
}
