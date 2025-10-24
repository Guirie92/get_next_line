/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:45:02 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/24 12:47:02 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (s == d || n == 0)
		return (dest);
	if (s > d)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n - 1;
		s += n - 1;
		while (n--)
			*d-- = *s--;
	}
	return (dest);
}

int	count_check_nl(char const *buffer, t_gnl_data *data)
{
	while (*buffer)
	{
		if (*buffer == '\n')
		{
			(data->len)++;
			return (NL_FOUND);
		}
		buffer++;
		(data->len)++;
	}
	return (NL_NOT_FOUND);
}

void	*cleanup(char **s_buf, t_tmp *tmp, t_gnl_data *data)
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

int	init_data(char **s_buf, t_tmp *tmp, t_gnl_data *data)
{
	if (!*s_buf)
	{
		*s_buf = malloc(BUFFER_SIZE + 1);
		if (!*s_buf)
			return (MEM_FAIL);
		(*s_buf)[0] = '\0';
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

int	check_alloc(t_tmp *tmp, size_t len)
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
