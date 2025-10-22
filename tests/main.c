/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 07:43:17 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/22 13:03:48 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <unistd.h> // For write() and close()
#include <fcntl.h>  // For open() and file flags (O_WRONLY, O_CREAT, etc.)
#include <stdio.h>  // For perror()
#include <stdlib.h> // For atoi() and exit()

int	main(int argc, char **argv)
{
	int fd = 0;
	char *line;
	size_t lines = 3;


	// {
	// 	fd = open("tests/TEXT_long_line_nl", O_RDONLY);
	// 	lines = 2;
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
	// return (0);

	
	{
		fd = open("tests/TEXT_variable_nls", O_RDONLY);
		lines = 13;
		if (fd == -1)
		{
		    perror("Error opening file");
		    exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < lines; i++)
		{
			printf("line[%zu]: %s\n", i, line = get_next_line(fd));
			free(line);
		}
    	close(fd);
	}
	return (0);

	/* subtest 1: */
	{
		fd = open("tests/TEXT", O_RDONLY);
		lines = 3;
		if (fd == -1)
		{
		    perror("Error opening file");
		    exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < lines; i++)
		{
			printf("line[%zu]: %s\n", i, line = get_next_line(fd));
			free(line);
		}
    	close(fd);

	}
	//return (0);
	
	/* subtest 2: */
	{
		fd = open("tests/TEXT_long_line_nl", O_RDONLY);
		lines = 2;
		if (fd == -1)
		{
		    perror("Error opening file");
		    exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < lines; i++)
		{
			printf("line[%zu]: %s\n", i, line = get_next_line(fd));
			free(line);
		}
    	close(fd);
	}
	//return (0);
	
	/* subtest 3: */
	{
		fd = open("tests/TEXT_long_line_nnl", O_RDONLY);
		lines = 2;
		if (fd == -1)
		{
		    perror("Error opening file");
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
		    perror("Error opening file");
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
	{
		fd = open("tests/TEXT_empty", O_RDONLY);
		lines = 2;
		if (fd == -1)
		{
		    perror("Error opening file");
		    exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < lines; i++)
		{
			printf("line[%zu]: %s\n", i, line = get_next_line(fd));
			free(line);
		}
    	close(fd);
	}
	
	/* subtest 6: */
	{
		fd = open("tests/TEXT_variable_nls", O_RDONLY);
		lines = 13;
		if (fd == -1)
		{
		    perror("Error opening file");
		    exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < lines; i++)
		{
			printf("line[%zu]: %s\n", i, line = get_next_line(fd));
			free(line);
		}
    	close(fd);
	}
	
	/* subtest 7: */
	{
		if (argc == 3)
		{
			fd = open(argv[2], O_RDONLY);
			
			if (fd == -1)
			{
			    perror("Error opening file");
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

	
	// #if 0
	// fd = open("tests/TEXT", O_RDONLY);
	// lines = 3;
	// #elif 1
	// fd = open("tests/TEXT_long_line_nl", O_RDONLY);
	// lines = 2;
	// #elif 1
	// fd = open("tests/TEXT_long_line_nnl", O_RDONLY);
	// lines = 2;
	// #elif 1
	// fd = open("tests/TEXT_long_line", O_RDONLY);
	// lines = 6;
	// #elif 1
	// fd = open("tests/TEXT_empty", O_RDONLY);
	// lines = 2;
	// #else
	// fd = open("tests/TEXT", O_RDONLY);
	// #endif
	


	// // 2. Error Check: 'open' returns -1 on failure
    // if (fd == -1)
    // {
    //     perror("Error opening file");
    //     exit(EXIT_FAILURE);
    // }

	// /* multi line test */
	// for (size_t i = 0; i < lines; i++)
	// {
	// 	printf("line[%zu]: %s\n", i, line = get_next_line(fd));
	// 	free(line);
	// }
    

    // // 3. Important: Close the file descriptor when finished
    // close(fd);

	return (0);
}
