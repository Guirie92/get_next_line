/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 07:43:17 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/19 17:22:21 by guillsan         ###   ########.fr       */
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

	if (argc == 3)
	{
		fd = open(argv[2], O_RDONLY);
	}
	else
		fd = open("tests/TEXT", O_RDONLY);

	// 2. Error Check: 'open' returns -1 on failure
    if (fd == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

	/* multi line test */
	size_t lines = 3;
	for (size_t i = 0; i < lines; i++)
	{
		printf("line[%zu]: %s\n", i, line = get_next_line(fd));
		free(line);
	}
    

    // 3. Important: Close the file descriptor when finished
    close(fd);

	return (0);
}
