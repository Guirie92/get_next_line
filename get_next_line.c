/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:15:10 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/23 23:32:55 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	process_reminder(char *s_buf, t_tmp *tmp, t_gnl_data *data);
static int	process_loop(char **s_buf, t_tmp *tmp, t_gnl_data *data, int fd);
static int	process_line(char **s_buf, t_tmp *tmp, t_gnl_data *data);
static int	process_final_line(char **s_buf, t_tmp *tmp, t_gnl_data *data);

char	*get_next_line(int fd)
{
	static char		*s_buf;
	t_tmp			tmp;
	t_gnl_data		data;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (init_data(&s_buf, &tmp, &data) == MEM_FAIL)
		return (NULL);
	data.ret_code = process_reminder(s_buf, &tmp, &data);
	if (data.ret_code == MEM_FAIL)
		return (cleanup(&s_buf, &tmp, &data));
	if (data.ret_code == NL_FOUND)
		return (data.line);
	data.bytes_read = read(fd, s_buf, BUFFER_SIZE);
	if (data.bytes_read == -1)
		return (cleanup(&s_buf, &tmp, &data));
	data.total_bytes = tmp.idx + data.bytes_read;
	data.len = tmp.idx;
	data.ret_code = process_loop(&s_buf, &tmp, &data, fd);
	if (data.ret_code == NL_FOUND)
		return (data.line);
	return (cleanup(&s_buf, &tmp, &data));
}

static int	process_reminder(char *s_buf, t_tmp *tmp, t_gnl_data *data)
{
	if (!*s_buf)
		return (NL_NOT_FOUND);
	if (count_check_nl(s_buf, data) == NL_FOUND)
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
		if (check_alloc(tmp, data->len) == MEM_FAIL)
			return (MEM_FAIL);
	ft_memmove((void *)tmp->buf, (void *)s_buf, data->len);
	return (NL_NOT_FOUND);
}

static int	process_loop(char **s_buf, t_tmp *tmp, t_gnl_data *data, int fd)
{
	while (data->bytes_read > 0)
	{
		(*s_buf)[data->bytes_read] = '\0';
		if (count_check_nl((const char *)*s_buf, data) == NL_FOUND)
		{
			if (process_line(s_buf, tmp, data) == MEM_FAIL)
				return (MEM_FAIL);
			return (NL_FOUND);
		}
		if (check_alloc(tmp, data->len) == MEM_FAIL)
			return (MEM_FAIL);
		ft_memmove((void *)&tmp->buf[tmp->idx],
			(void *)*s_buf, data->bytes_read);
		tmp->idx = data->len;
		data->bytes_read = read(fd, *s_buf, BUFFER_SIZE);
		data->total_bytes += data->bytes_read;
	}
	if (data->bytes_read == 0 && data->len > 0)
	{
		if (process_final_line(s_buf, tmp, data) == MEM_FAIL)
			return (MEM_FAIL);
		return (NL_FOUND);
	}
	return (NL_NOT_FOUND);
}

static int	process_line(char **s_buf, t_tmp *tmp, t_gnl_data *data)
{
	if (check_alloc(tmp, data->len) == MEM_FAIL)
		return (MEM_FAIL);
	ft_memmove((void *)&tmp->buf[tmp->idx], (void *)*s_buf, data->bytes_read);
	data->line = malloc((data->len + 1) * sizeof(char));
	if (!data->line)
		return (MEM_FAIL);
	ft_memmove((void *)data->line, (void *)tmp->buf, data->len);
	data->line[data->len] = '\0';
	tmp->idx = data->len;
	ft_memmove((void *)*s_buf, (void *)&tmp->buf[tmp->idx],
		data->total_bytes - tmp->idx);
	(*s_buf)[data->total_bytes - tmp->idx] = '\0';
	free(tmp->buf);
	return (NL_FOUND);
}

static int	process_final_line(char **s_buf, t_tmp *tmp, t_gnl_data *data)
{
	data->line = malloc((data->len + 1) * sizeof(char));
	if (!(data->line))
		return (MEM_FAIL);
	ft_memmove((void *)data->line, (void *)tmp->buf, data->len);
	data->line[data->len] = '\0';
	free(tmp->buf);
	free(*s_buf);
	*s_buf = NULL;
	return (NL_FOUND);
}
