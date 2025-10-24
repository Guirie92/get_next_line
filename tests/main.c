/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 07:43:17 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/24 22:32:37 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BONUS 0

#if BONUS
# include "../get_next_line_bonus.h"
#else
# include "../get_next_line.h"
#endif
#define LOGGING 1
#define TIMING_ENABLED 1
#define TIMING_TEST 1
#include "logging.h"
#include "timing.h"
#include <unistd.h> /* For write() and close() */
#include <fcntl.h>  /* For open() and file flags (O_WRONLY, O_CREAT, etc.) */
#include <stdio.h>  /* For perror() */
#include <stdlib.h> /* For atoi() and exit() */

int	main(int argc, char **argv)
{
	int fd = 0;
	char *line;
	size_t lines = 3;


#if 1

 	TIMING_DECLARE(t);
 	TIMING_START(t);
	
 	//fd = open("tests/TEXT_timing_test", O_RDONLY);
 	fd = open("tests/TEXT_many_l", O_RDONLY);
	lines = 1000; 
	if (fd == -1)
	{
	    perror("Error opening file for timing test");
	    exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < lines; i++)
	{
		TIMING_START(t);
		line = get_next_line(fd);
		TIMING_STOP(t);
		TIMING_LOG_SEC_MS(t, "[TIMING] line[%zu], in", i);
		//printf("line[%zu]: %s\n", i, line);
		free(line);
	}
	close(fd);
	
	TIMING_STOP(t);
	TIMING_LOG_SEC_MS(t, "total time");
	
	
 	TIMING_START(t);
	
 	fd = open("tests/TEXT_timing_test", O_RDONLY);
 	//fd = open("tests/TEXT_many_l", O_RDONLY);
	lines = 6;
	if (fd == -1)
	{
	    perror("Error opening file for timing test");
	    exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < lines; i++)
	{
		//TIMING_START(t);
		line = get_next_line(fd);
		//TIMING_STOP(t);
		//TIMING_LOG_SEC_MS(t, "[TIMING] line[%zu], in", i);
		//printf("line[%zu]: %s\n", i, line);
		free(line);
	}

	TIMING_STOP(t);
	TIMING_LOG_SEC_MS(t, "total time");
		
    close(fd);
 	return (0);

#endif

#if BONUS
	
	(void)argc;
	(void)argv;
	/* subtest 1: */
	{
		int fd_2 = 0;
		fd = open("tests/TEXT_bonus", O_RDONLY);
		fd_2 = open("tests/TEXT_bonus_2", O_RDONLY);
		lines = 5;
		if (fd == -1)
		{
		    perror("Error opening file 1");
		    exit(EXIT_FAILURE);
		}
		if (fd_2 == -1)
		{
		    perror("Error opening file 2");
		    exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < lines; i++)
		{
			printf("line fd_1[%zu]: %s\n", i, line = get_next_line(fd));
			free(line);
			printf("line fd_2[%zu]: %s\n", i, line = get_next_line(fd_2));
			free(line);
		}
    	close(fd);
    	close(fd_2);
	}
	
#else

	/* subtest 1: */
	// {
	// 	fd = open("tests/TEXT", O_RDONLY);
	// 	lines = 3;
	// 	if (fd == -1)
	// 	{
	// 	    perror("Error opening file");
	// 	    exit(EXIT_FAILURE);
	// 	}
	// 	for (size_t i = 0; i < lines; i++)
	// 	{
	// 		printf("line[%zu]: %s\n", i, line = get_next_line(fd));
	// 		free(line);
	// 	}
    // 	close(fd);
	// }
	
	/* subtest 2: */
	{
		fd = open("tests/TEXT_long_line_nl", O_RDONLY);
		lines = 2;
		if (fd == -1)
		{
		    perror("Error opening file 2");
		    exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < lines; i++)
		{
			printf("line[%zu]: %s\n", i, line = get_next_line(fd));
			free(line);
		}
    	close(fd);
	}
	
	/* subtest 3: */
	{
		fd = open("tests/TEXT_long_line_nnl", O_RDONLY);
		lines = 2;
		if (fd == -1)
		{
		    perror("Error opening file 3");
		    exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < lines; i++)
		{
			printf("line[%zu]: %s\n", i, line = get_next_line(fd));
			free(line);
		}
    	close(fd);
	}

	/* subtest 4: */
	{
		fd = open("tests/TEXT_long_line", O_RDONLY);
		lines = 6;
		if (fd == -1)
		{
		    perror("Error opening file 4");
		    exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < lines; i++)
		{
			printf("line[%zu]: %s\n", i, line = get_next_line(fd));
			free(line);
		}
    	close(fd);
	}

	/* subtest 5: */
	// {
	// 	fd = open("tests/TEXT_empty", O_RDONLY);
	// 	lines = 2;
	// 	if (fd == -1)
	// 	{
	// 	    perror("Error opening file 5");
	// 	    exit(EXIT_FAILURE);
	// 	}
	// 	for (size_t i = 0; i < lines; i++)
	// 	{
	// 		printf("line[%zu]: %s\n", i, line = get_next_line(fd));
	// 		free(line);
	// 	}
    // 	close(fd);
	// }
	
	/* subtest 6: */
	{
		fd = open("tests/TEXT_variable_nls", O_RDONLY);
		lines = 13;
		if (fd == -1)
		{
		    perror("Error opening file 6");
		    exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < lines; i++)
		{
			printf("line[%zu]: %s\n", i, line = get_next_line(fd));
			free(line);
		}
    	close(fd);
	}
	
	/* subtest 7: args */
	{
		if (argc == 2)
		{
			fd = open(argv[1], O_RDONLY);
			lines = 5;
			if (fd == -1)
			{
			    perror("Error opening file (args)");
			    exit(EXIT_FAILURE);
			}
			for (size_t i = 0; i < lines; i++)
			{
				printf("line[%zu]: %s\n", i, line = get_next_line(fd));
				free(line);
			}
    		close(fd);
		}
	}

	/* subtest 8: Standard Input (SI) */
	{
		fd = 0;
		lines = 4;
		if (fd == -1)
		{
		    perror("Error printing SI");
		    exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < lines; i++)
		{
			printf("line[%zu]: %s\n", i, line = get_next_line(fd));
			free(line);
		}
    	close(fd);
	}

#endif
	return (0);
}
