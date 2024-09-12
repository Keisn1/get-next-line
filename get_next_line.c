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

char	*crud_stash(t_op op, char *new_stash)
{
	static char	*stash = NULL;
	char		*tmp;

	if (op == SET_STASH) {
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

bool check_newline() {

	char* stash = crud_stash(GET_STASH, "");
	if (!stash)
		return false;
	size_t count = 0;
	while (count < ft_strlen(stash)) {
		if (stash[count] == '\n') {
			free(stash);
			return true;
		}
		count++;
	}
	free(stash);
	return false;
}

char* check_newline_and_update() {
	char* stash = crud_stash(GET_STASH, "");
	size_t count = 0;
	if (!stash)
		return stash;
	while (count < ft_strlen(stash)) {
		if (stash[count++] == '\n') {
			if (count == ft_strlen(stash))
				crud_stash(DELETE_STASH, "");
			else
				crud_stash(SET_STASH, stash+count);
			char* ret = ft_get_empty_str(count+1);
			ft_memcpy(ret, stash, count);
			ret[count] = '\0';
			free(stash);
			return ret;
		}
	}
	crud_stash(DELETE_STASH, "");
	return stash;
}

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	int		bytes_read;
	char	*ret;
	char	*buf_string;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf_string = buffer_to_string(buffer, bytes_read);
		if (!buf_string)
			return NULL;
		crud_stash(UPDATE_STASH, buf_string);
		free(buf_string);
		if (check_newline())
			break;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return NULL;
	ret = check_newline_and_update();
	return (ret);
}

/* char	*add_buf_to_stash(char *stash, char buf[BUFFER_SIZE], int bytes_read) */
/* { */
/* 	int		size_stash; */
/* 	int		size_new; */
/* 	char	*new_stash; */

/* 	size_stash = 0; */
/* 	if (stash) */
/* 		size_stash = ft_strlen(stash); */

/* 	size_new = size_stash + bytes_read + 1; */

/* 	new_stash = (char *)malloc(size_new); */
/* 	if (!new_stash) */
/* 		return (NULL); */
/* 	*new_stash = '\0'; */
/* 	if (stash) */
/* 		ft_strlcat(new_stash, stash, size_new); */

/* 	ft_memcpy(new_stash + size_stash, buf, bytes_read); */
/* 	new_stash[size_new - 1] = '\0'; */
/* 	return (new_stash); */
/* } */

/* char	*update_stash(char buf[BUFFER_SIZE], int bytes_read, bool new_file, */
/* 		char *reset_stash, bool set_stash_null) */
/* { */
/* 	static char	*stash = NULL; */
/* 	char		*new_stash; */

/* 	if (set_stash_null) { */
/* 		free(stash); */
/* 		stash = NULL; */
/* 		return (stash); */
/* 	} */
/* 	if (reset_stash) */
/* 	{ */
/* 		char* new_stash = ft_strdup(reset_stash); */
/* 		free(stash); */
/* 		stash = new_stash; */
/* 		return (stash); */
/* 	} */
/* 	if (new_file) */
/* 	{ */
/* 		free(stash); */
/* 		stash = NULL; */
/* 		return (stash); */
/* 	} */
/* 	if (!buf) { */
/* 		if (stash) */
/* 			return (ft_strdup(stash)); */
/* 		return (NULL); */
/* 	} */

/* 	new_stash = add_buf_to_stash(stash, buf, bytes_read); */
/* 	free(stash); */
/* 	stash = new_stash; */
/* 	return (ft_strdup(stash)); */
/* } */

/* char *check_newline(char *stash) { */
/* 	size_t		idx; */
/* 	char* ret; */
/* 	if (stash) */
/* 	{ */
/* 		idx = 0; */
/* 		while (stash[idx] != '\n' && idx < ft_strlen(stash)) */
/* 			idx++; */
/* 		if (idx < ft_strlen(stash)) */
/* 		{ */
/* 			ret = ft_get_empty_str(idx + 2); */
/* 			ft_memcpy(ret, stash, idx + 1); */
/* 			ret[idx + 1] = '\0'; */
/* 			if (idx + 1 < ft_strlen(stash)) { */
/* 				update_stash(NULL, 0, false, stash + idx + 1, false); */
/* 			} else { */
/* 				update_stash(NULL, 0, false, NULL, true); */
/* 			} */
/* 			return (ret); */
/* 		} */
/* 		return (stash); */
/* 	} */
/* 	return (NULL); */
/* } */

/* bool found_newline(char *s) { */
/* 	size_t idx = 0; */
/* 	if (!s) */
/* 		return (false); */
/* 	while (s[idx] != '\n' && idx < ft_strlen(s)) */
/* 		idx++; */

/* 	if (idx < ft_strlen(s)) */
/* 		return (true); */
/* 	return (false); */
/* } */

/* char	*get_next_line(int fd) */
/* { */
/* 	static int	old_fd = -1; */
/* 	char		buffer[BUFFER_SIZE]; */
/* 	int			bytes_read; */
/* 	char		*ret; */
/* 	bool		new_file; */
/* 	/\* char		*stash; *\/ */

/* 	new_file = false; */
/* 	if (fd != old_fd) */
/* 		new_file = true; */
/* 	old_fd = fd; */
/* 	ret = update_stash(NULL, 0, new_file, NULL, false); */
/* 	new_file = false; */
/* 	ret = check_newline(ret); */
/* 	if (found_newline(ret)) { */
/* 		return (ret); */
/* 	} */
/* 	free(ret); */
/* 	ret = NULL; */
/* 	bytes_read = read(fd, buffer, BUFFER_SIZE); */
/* 	while (bytes_read > 0) */
/* 	{ */
/* 		free(ret); */
/* 		ret = update_stash(buffer, bytes_read, new_file, NULL, false); */
/* 		ret = check_newline(ret); */
/* 		if (found_newline(ret)) { */
/* 			return (ret); */
/* 		} */
/* 		/\* if (ret[ft_strlen(ret) - 1] == '\n') *\/ */
/* 		/\* 	break ; *\/ */
/* 		new_file = false; */
/* 		bytes_read = read(fd, buffer, BUFFER_SIZE); */
/* 	} */
/* 	return (ret); */
/* } */
