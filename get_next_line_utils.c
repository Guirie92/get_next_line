/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:45:02 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/19 22:19:12 by guillsan         ###   ########.fr       */
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

size_t	check_gnl_init_data(t_gnl_data **s_gnl, size_t *len)
{
	(*len) = 0;
	if (*s_gnl)
		return (SUCCESS);
	(*s_gnl) = malloc(sizeof(t_gnl_data));
	if (!s_gnl)
		return (MEM_FAIL);
	(*s_gnl)->buf = NULL;
	(*s_gnl)->idx = 0;
	(*s_gnl)->len = 0;
	(*s_gnl)->alloc_size = ALLOC_MIN;
	return (SUCCESS);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	if (n == 0 || (!dest && !src))
		return (dest);
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	int i = 0;
	while (n--)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	cpy_next_line(const char *buffer, char *line)
{
	while (*buffer)
	{
		if (*buffer == '\n'|| *buffer == '\0')
		{
			*line = *buffer;
			break ;
		}
		*line++ = *buffer++;
	}
}

size_t	count_check_next_line(char const *buffer, size_t *len)
{
	if (!*buffer)
		return (NL_NOT_FOUND);
	while (1)
	{
		if (*buffer == '\n' || *buffer == '\0')
		{
			(*len)++;
			return (NL_FOUND);
		}
		buffer++;
		(*len)++;
	}
	return (NL_NOT_FOUND);
}
