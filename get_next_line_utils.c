/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:45:02 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/23 15:19:35 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	const unsigned char	*s;
// 	unsigned char		*d;

// 	if (n == 0 || (!dest && !src))
// 		return (dest);
// 	s = (const unsigned char *)src;
// 	d = (unsigned char *)dest;
// 	while (n--)
// 		*d++ = *s++;
// 	return (dest);
// }

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	unsigned char	*p;
// 	void			*ptr;
// 	size_t			n;

// 	if (nmemb == 0 || size == 0)
// 		return (malloc(0));
// 	if (nmemb > SIZE_MAX / size)
// 		return (NULL);
// 	ptr = malloc(nmemb * size);
// 	if (!ptr)
// 		return (NULL);
// 	n = nmemb * size;
// 	p = (unsigned char *)ptr;
// 	while (n--)
// 		*(p++) = 0;
// 	return (ptr);
// }

// size_t	check_gnl_init_data(t_tmpbuf **s_gnl, size_t *len)
// {
// 	(*len) = 0;
// 	if (*s_gnl)
// 		return (SUCCESS);
// 	(*s_gnl) = malloc(sizeof(t_tmpbuf));
// 	if (!s_gnl)
// 		return (MEM_FAIL);
// 	(*s_gnl)->buf = NULL;
// 	(*s_gnl)->idx = 0;
// 	(*s_gnl)->len = 0;
// 	(*s_gnl)->capacity = ALLOC_MIN;
// 	return (SUCCESS);
// }

// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	const unsigned char	*s;
// 	unsigned char		*d;

// 	if (n == 0 || (!dest && !src))
// 		return (dest);
// 	s = (const unsigned char *)src;
// 	d = (unsigned char *)dest;
// 	int i = 0;
// 	while (n--)
// 	{
// 		d[i] = s[i];
// 		i++;
// 	}
// 	return (dest);
// }

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

// void	*ft_memmove(void *dest, const void *src, size_t n)
// {
// 	const unsigned char	*s;
// 	unsigned char		*d;
// 	size_t				i;

// 	s = (const unsigned char *)src;
// 	d = (unsigned char *)dest;
// 	if (!s || !d)
// 		return (NULL);
// 	if (s == d || n == 0)
// 		return (dest);
// 	if (s > d)
// 	{
// 		i = 0;
// 		while (n--)
// 		{
// 			d[i] = s[i];
// 			i++;
// 		}
// 	}
// 		//return (ft_memcpy(dest, src, n));
// 	else
// 	{
// 		// d += n - 1;
// 		// s += n - 1;
// 		i = n - 1;
// 		while (n--)
// 		{
// 			d[i] = s[i];
// 			//printf("addr d: %p  |  addr s: %p\n", &d[i], &s[i]);
// 			//fflush(stdout);
// 			i--;
// 		}
// 			//*d-- = *s--;
// 	} // addr 0x4a8e04e
// 	return (dest);
// }

size_t	count_check_next_line(char const *buffer, t_gnl_data *data)
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

void	*cleanup(char **s_buf, t_tmpbuf *tmp, t_gnl_data *data)
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

size_t	init_data(char **buf, t_tmpbuf *tmp, t_gnl_data *data)
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