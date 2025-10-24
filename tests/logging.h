/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:24:15 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/24 17:53:14 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
# define LOGGING_H

# ifndef LOGGING
#  define LOGGING 1
# endif

# if LOGGING
#  include <unistd.h>
#  include <stdio.h>

#  define LOG_WRITE(fd, buf, count) \
    do { ssize_t _log_write_ret = write((fd), (buf), (count)); (void)_log_write_ret; } while (0)
	
#  define LOG_PRINT(fmt, ...)   \
    do { fprintf(stdout, (fmt), ##__VA_ARGS__); } while (0)

#  define LOG_ERROR(fmt, ...)   \
    do { fprintf(stderr, (fmt), ##__VA_ARGS__); } while (0)
	
# else

#  define LOG_WRITE(fd, buf, count) ((void)0)
#  define LOG_PRINT(fmt, ...)       ((void)0)
#  define LOG_ERROR(fmt, ...)       ((void)0)

# endif /* LOGGING */

#endif /* LOGGING_H */