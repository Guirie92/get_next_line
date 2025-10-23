/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 07:45:28 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/23 22:04:39 by guillsan         ###   ########.fr       */
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

# define ALLOC_MIN 32
# define ALLOC_ADD_SIZE 65536
# define ALLOC_MUL_CAP 1048576

typedef enum e_return_code
{
	NL_NOT_FOUND = 0,
	NL_FOUND = 1,
	MEM_FAIL = 2,
	SUCCESS = 3
}	t_return_code;

typedef struct s_tmpbuf
{
	char		*buf;
	size_t		idx;
	size_t		capacity;
}	t_tmpbuf;

typedef struct s_gnl_data
{
	char		*line;
	size_t		total_bytes;
	ssize_t		bytes_read;
	size_t		ret_code;
	size_t		len;
}	t_gnl_data;

void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	count_check_nl(const char *buffer, t_gnl_data *data);
void	*cleanup(char **s_buf, t_tmpbuf *tmp, t_gnl_data *data);
size_t	init_data(char **buf, t_tmpbuf *tmp, t_gnl_data *data);
size_t	check_alloc(t_tmpbuf *tmp, size_t len);

char	*get_next_line(int fd);

#endif // GET_NEXT_LINE_H