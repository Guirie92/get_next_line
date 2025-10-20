/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 07:45:28 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/19 22:20:31 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif // BUFFER_SIZE

# define ALLOC_MIN 1 // change back to 32
# define ALLOC_CAP 256

typedef enum e_return_code
{
	NL_NOT_FOUND = 0,
	NL_FOUND = 1,
	MEM_FAIL = 2,
	SUCCESS = 3
}	t_return_code;

typedef struct s_gnl_data
{
	char		*buf;
	size_t		idx;
	size_t		len;
	size_t		alloc_size;
}	t_gnl_data;


void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	check_gnl_init_data(t_gnl_data **s_gnl, size_t *len);
void	cpy_next_line(const char *buffer, char *line);
size_t	count_check_next_line(const char *buffer, size_t *len);

char	*get_next_line(int fd);

#endif // GET_NEXT_LINE_H