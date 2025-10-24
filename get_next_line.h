/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 07:45:28 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/24 12:47:17 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# define ALLOC_MIN 32
# define ALLOC_ADD_SIZE 65536
# define ALLOC_MUL_CAP 1048576

typedef enum e_return_code
{
	MEM_FAIL = -1,
	NL_NOT_FOUND = 0,
	NL_FOUND = 1,
	SUCCESS = 2
}	t_return_code;

typedef struct s_tmp
{
	char		*buf;
	size_t		idx;
	size_t		capacity;
}	t_tmp;

typedef struct s_gnl_data
{
	char		*line;
	size_t		total_bytes;
	ssize_t		bytes_read;
	size_t		len;
	int			ret_code;
}	t_gnl_data;

char	*get_next_line(int fd);

int		init_data(char **s_buf, t_tmp *tmp, t_gnl_data *data);
int		count_check_nl(const char *buffer, t_gnl_data *data);
int		check_alloc(t_tmp *tmp, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*cleanup(char **s_buf, t_tmp *tmp, t_gnl_data *data);

#endif // GET_NEXT_LINE_H