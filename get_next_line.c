/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:15:10 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/19 22:34:53 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <string.h>
#include <stdio.h> 


static size_t	process_rest(t_gnl_data *s_gnl, char **line, size_t *len)
{
	if (!(s_gnl->buf) || !(s_gnl->buf[s_gnl->idx]))
		return (NL_NOT_FOUND);
	if (count_check_next_line(&s_gnl->buf[s_gnl->idx], len) == NL_FOUND)
	{
		*line = malloc(*len * sizeof(char));
		if (!*line)
			return (MEM_FAIL);
		ft_memcpy((void *)*line, (void *)&s_gnl->buf[s_gnl->idx], (*len - 1));
		(*line)[*len - 1] = '\0';
		s_gnl->idx += *len;
		return (NL_FOUND);
	}
	// TODO
	return (NL_NOT_FOUND);
}

static char	*alloc_buffer(t_gnl_data *s_gnl)
{
	size_t	alloc_size;

	alloc_size = s_gnl->alloc_size;
	if (s_gnl->alloc_size < ALLOC_MIN)
	{
		s_gnl->buf = malloc(ALLOC_MIN * sizeof(char));
		s_gnl->len = ALLOC_MIN;
	}
	else if (s_gnl->alloc_size * 2 < ALLOC_CAP)
	{
		alloc_size *= 2;
		s_gnl->buf = malloc(alloc_size * sizeof(char));
		s_gnl->len = alloc_size;
	}
	else
	{
		s_gnl->buf = malloc(alloc_size * sizeof(char));
		s_gnl->len = alloc_size;
	}
	return (s_gnl->buf);
}

static char	*realloc_buffer(char *tmp, t_gnl_data *s_gnl)
{
	size_t	alloc_size;

	tmp = malloc(s_gnl->alloc_size * sizeof(char));
	if (!tmp)
		return (MEM_FAIL);
	alloc_size = s_gnl->alloc_size;
	if (s_gnl->alloc_size < ALLOC_MIN)
	{
		s_gnl->buf = malloc(ALLOC_MIN * sizeof(char));
		s_gnl->len = ALLOC_MIN;
	}
	else if (s_gnl->alloc_size * 2 < ALLOC_CAP)
	{
		alloc_size *= 2;
		s_gnl->buf = malloc(alloc_size * sizeof(char));
		s_gnl->len = alloc_size;
	}
	else
	{
		s_gnl->buf = malloc(alloc_size * sizeof(char));
		s_gnl->len = alloc_size;
	}
	return (s_gnl->buf);
}

char	*get_next_line(int fd)
{
	static t_gnl_data	*s_gnl;
	char				*tmp;
	char				*line;
	size_t				bytes_read;
	size_t				len;

	if (check_gnl_init_data(&s_gnl, &len) == MEM_FAIL)
		return (NULL);


	/* process rest */
	bytes_read = process_rest(s_gnl, &line, &len);
	if (bytes_read == MEM_FAIL)
		return (NULL);
	if (bytes_read == NL_FOUND)
		return (line);


	/* alloc */
	free(s_gnl->buf);
	if (!alloc_buffer(s_gnl))
		return (NULL);




	bytes_read = read(fd, s_gnl->buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		s_gnl->buf[bytes_read] = '\0';
		len = 0;
		if (count_check_next_line((const char *)&s_gnl->buf[s_gnl->idx], &len))
		{
			//process_line();
			//return (line);
			line = malloc(len * sizeof(char));
			if (!line)
				return (NULL);
			ft_memcpy((void *)line, (void *)&s_gnl->buf[s_gnl->idx], len - 1);
			line[len - 1] = '\0';
			s_gnl->idx += len;
			return (line);
		}


		if (s_gnl->alloc_size < bytes_read)
			if (realloc_buffer(tmp, s_gnl) == MEM_FAIL)
				return (NULL);


		bytes_read = read(fd, s_gnl->buf, BUFFER_SIZE);
	}
	// if (bytes_read == 0) /* EOF */
	// 	return (NULL);


	count_check_next_line((const char *)&s_gnl->buf[s_gnl->idx], &len);
	return (strdup(s_gnl->buf));
}



// ---------------------------------------------------- //
// --------------------- CONCEPTS --------------------- //
// ---------------------------------------------------- //


// char	*get_next_single_heap_buffer(int fd)
// {
// 	static char		*s_buffer;
// 	size_t			bytes_read;

// 	if (s_buffer && *s_buffer)
// 	{
// 		// process the rest
// 	}
// 	s_buffer = malloc(BUFFER_SIZE * sizeof(char));
// 	if (!s_buffer)
// 		return (NULL);
// 	bytes_read = read(fd, s_buffer, BUFFER_SIZE - 1);
// 	while (bytes_read > 0)
// 	{
// 		s_buffer[bytes_read] = '\0';
// 		bytes_read = read(fd, s_buffer, BUFFER_SIZE - 1);
// 	}
// 	return (ft_strdup(s_buffer));
// }

// char	*get_next_line_simple(int fd)
// {
// 	static char	buffer[BUFFER_SIZE];
// 	size_t		bytes_read;

// 	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
// 	while (bytes_read > 0)
// 	{
// 		buffer[bytes_read] = '\0';
// 		bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
// 	}

// 	return (ft_strdup(buffer));
// }