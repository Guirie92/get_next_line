/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:15:10 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/23 11:19:37 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	check_realloc(t_tmpbuf *tmp, size_t len)
{
	void	*new_buf;
	size_t	new_capacity;

	if (tmp->capacity >= len + BUFFER_SIZE)
		return (SUCCESS);
	new_capacity = tmp->capacity;
	if (new_capacity == 0)
		new_capacity = ALLOC_MIN;
	else if (new_capacity > ALLOC_MUL_CAP)
		new_capacity += ALLOC_ADD_SIZE;
	else
		new_capacity *= 2;
	if (new_capacity < len + BUFFER_SIZE)
		new_capacity = len + BUFFER_SIZE;
	new_buf = malloc(new_capacity + 1);
	if (!new_buf)
		return (MEM_FAIL);
	if (tmp->buf)
	{
		ft_memmove(new_buf, (void *)tmp->buf, tmp->idx);
		free(tmp->buf);
	}
	tmp->buf = (char *)new_buf;
	tmp->capacity = new_capacity;
	return (SUCCESS);
}

static size_t	reminder(char *s_buf, t_tmpbuf *tmp, t_gnl_data *data)
{
	if (!*s_buf)
		return (NL_NOT_FOUND);
	if (count_check_next_line(s_buf, data) == NL_FOUND)
	{
		data->line = malloc((data->len + 1) * sizeof(char));
		if (!data->line)
			return (MEM_FAIL);
		ft_memmove((void *)data->line, (void *)s_buf, data->len);
		(data->line)[data->len] = '\0';
		ft_memmove((void *)s_buf, (void *)(s_buf + data->len),
			(BUFFER_SIZE - data->len) + 1);
		return (NL_FOUND);
	}
	tmp->idx = data->len;
	if (tmp->capacity < data->len + 1)
		if (check_realloc(tmp, data->len) == MEM_FAIL)
			return (MEM_FAIL);
	ft_memmove((void *)tmp->buf, (void *)s_buf, data->len);
	return (NL_NOT_FOUND);
}

static void	*cleanup(char **s_buf, t_tmpbuf *tmp, t_gnl_data *data)
{
	if (*s_buf)
		free(*s_buf);
	*s_buf = NULL;
	if (tmp->buf)
		free(tmp->buf);
	if (data->line)
		free(data->line);
	return (NULL);
}

static size_t	init_data(char **buf, t_tmpbuf *tmp, t_gnl_data *data)
{
	if (!*buf)
	{
		*buf = malloc(BUFFER_SIZE + 1);
		if (!*buf)
			return (MEM_FAIL);
		(*buf)[0] = '\0';
	}
	data->bytes_read = 0;
	data->total_bytes = 0;
	data->len = 0;
	data->line = NULL;
	tmp->idx = 0;
	tmp->buf = NULL;
	tmp->capacity = 0;
	return (SUCCESS);
}


char	*get_next_line(int fd)
{
	static char		*s_buf;
	t_tmpbuf		tmp;
	t_gnl_data		data;

	if (fd == -1)
		return (NULL);
	if (init_data(&s_buf, &tmp, &data) == MEM_FAIL)
		return (NULL);

	/* process reminder */
	data.bytes_read = reminder(s_buf, &tmp, &data);
	if (data.bytes_read == MEM_FAIL)
		return (cleanup(&s_buf, &tmp, &data));
	if (data.bytes_read == NL_FOUND)
		return (data.line);


	data.bytes_read = read(fd, s_buf, BUFFER_SIZE);
	if (data.bytes_read == -1)
		return (cleanup(&s_buf, &tmp, &data));

	//tmp.len += bytes_read + len;
	data.total_bytes = tmp.idx + data.bytes_read;
	data.len = tmp.idx;
	while (data.bytes_read > 0)
	{
		s_buf[data.bytes_read] = '\0';
		if (count_check_next_line((const char *)s_buf, &data) == NL_FOUND)
		{
			if (check_realloc(&tmp, data.len) == MEM_FAIL)
				return (cleanup(&s_buf, &tmp, &data));
			ft_memmove((void *)&tmp.buf[tmp.idx], (void *)s_buf, data.bytes_read);
			data.line = malloc((data.len + 1) * sizeof(char));
			if (!data.line)
				return (cleanup(&s_buf, &tmp, &data));
			ft_memmove((void *)data.line, (void *)tmp.buf, data.len);
			data.line[data.len] = '\0';
			tmp.idx = data.len;
			ft_memmove((void *)s_buf, (void *)&tmp.buf[tmp.idx], data.total_bytes - tmp.idx);
			s_buf[data.total_bytes - tmp.idx] = '\0';
			free(tmp.buf);
			return (data.line);
		}

		if (check_realloc(&tmp, data.len) == MEM_FAIL)
			return (cleanup(&s_buf, &tmp, &data));
		ft_memmove((void *)&tmp.buf[tmp.idx], (void *)s_buf, data.bytes_read);
		tmp.idx = data.len;
		data.bytes_read = read(fd, s_buf, BUFFER_SIZE);
		data.total_bytes += data.bytes_read;
	}
	if (data.bytes_read == 0 && data.len > 0)
	{
		data.line = malloc((data.len + 1) * sizeof(char));
		if (!(data.line))
			return (cleanup(&s_buf, &tmp, &data));
		ft_memmove((void *)data.line, (void *)tmp.buf, data.len);
		data.line[data.len] = '\0';
		free(tmp.buf);
		free(s_buf);
		s_buf = NULL;
		return (data.line);
	}
	return (cleanup(&s_buf, &tmp, &data));
}

char	*get_next_line(int fd)
{
	static char		*s_buf;
	t_tmpbuf		tmp;
	t_gnl_data		data;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	// Initialize buffers
	if (init_data(&s_buf, &tmp, &data) == MEM_FAIL)
		return (NULL);

	// Process existing buffer first
	/* process reminder */
	if (process_reminder(s_buf, &tmp, &data) == NL_FOUND)
		return (data.line);

	// Read loop
	while ((data.bytes_read = read(fd, s_buf, BUFFER_SIZE)) > 0)
	{
		s_buf[data.bytes_read] = '\0';
		if (process_chunk(s_buf, &tmp, &data) == NL_FOUND)
			return (data.line);
	}

	// Handle end of file
	if (data.bytes_read == 0 && tmp.idx > 0)
		return (extract_final_line(&tmp, &data));

	return (cleanup(&s_buf, &tmp, &data));
}


char	*get_next_line(int fd)
{
	static char		*s_buf;
	t_tmpbuf		tmp;
	t_gnl_data		data;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (init_data(&s_buf, &tmp, &data) == MEM_FAIL)
		return (NULL);
	data.bytes_read = reminder(s_buf, &tmp, &data);
	if (data.bytes_read == MEM_FAIL)
		return (cleanup(&s_buf, &tmp, &data));
	if (data.bytes_read == NL_FOUND)
		return (data.line);
	data.bytes_read = read(fd, s_buf, BUFFER_SIZE);
	if (data.bytes_read == -1)
		return (cleanup(&s_buf, &tmp, &data));
	data.total_bytes = tmp.idx + data.bytes_read;
	data.len = tmp.idx;
	while (data.bytes_read > 0)
	{
		s_buf[data.bytes_read] = '\0';
		if (process_chunk(s_buf, &tmp, &data) == NL_FOUND)
			return (data.line);
	}
	if (data.bytes_read == 0 && tmp.idx > 0)
		return (extract_final_line(&tmp, &data));
	return (cleanup(&s_buf, &tmp, &data));
}

char	*get_next_line(int fd)
{
	static char		*s_buf;
	t_tmpbuf		tmp;
	t_gnl_data		data;
	size_t			ret_code;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (init_data(&s_buf, &tmp, &data) == MEM_FAIL)
		return (NULL);
	data.bytes_read = reminder(s_buf, &tmp, &data);
	if (data.bytes_read == MEM_FAIL)
		return (cleanup(&s_buf, &tmp, &data));
	if (data.bytes_read == NL_FOUND)
		return (data.line);
	data.bytes_read = read(fd, s_buf, BUFFER_SIZE);
	if (data.bytes_read == -1)
		return (cleanup(&s_buf, &tmp, &data));
	data.total_bytes = tmp.idx + data.bytes_read;
	data.len = tmp.idx;
	ret_code = process_loop();
	if (ret_code == MEM_FAIL)
		return (cleanup(&s_buf, &tmp, &data));
	else if (ret_code == NL_FOUND)
		return (data.line);
	if (data.bytes_read == 0 && tmp.idx > 0)
		return (extract_final_line(&tmp, &data));
	return (cleanup(&s_buf, &tmp, &data));
}
