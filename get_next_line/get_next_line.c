/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:07:29 by gagulhon          #+#    #+#             */
/*   Updated: 2025/12/02 11:30:57 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_extract_line(char *stash)
{
	size_t	len;

	if (!stash || !stash[0])
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	return (ft_substr(stash, 0, len));
}

static char	*ft_clean_stash(char *stash)
{
	size_t	start;
	char	*new_stash;

	if (!stash)
		return (NULL);
	start = 0;
	while (stash[start] && stash[start] != '\n')
		start++;
	if (stash[start] == '\n')
		start++;
	if (!stash[start])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, start, ft_strlen(stash) - start);
	free(stash);
	return (new_stash);
}

static char	*ft_read_to_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(stash), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_strjoin_free(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
	}
	return (free(buffer), stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_extract_line(stash[fd]);
	stash[fd] = ft_clean_stash(stash[fd]);
	return (line);
}

// cc -D BUFFER_SIZE=2 get_next_line.c get_next_line_utils.c && ./a.out
// #include <fcntl.h>
// int main(void)
// {
// 	int fd[4];
// 	int i = 1;
// 	char *line;

// 	fd[0] = open("file1", O_RDONLY);
// 	fd[1] = open("file2", O_RDONLY);
// 	fd[2] = open("file3", O_RDONLY);
// 	fd[3] = open("bsb.txt", O_RDONLY);
// 	__builtin_printf("\n1 line file1:\n");
// 	__builtin_printf("%s", get_next_line(fd[0]));
// 	__builtin_printf("\n2 lines file2:\n");
// 	__builtin_printf("%s", get_next_line(fd[1]));
// 	__builtin_printf("%s", get_next_line(fd[1]));
// 	__builtin_printf("\n3 lines file3:\n");
// 	__builtin_printf("%s", get_next_line(fd[2]));
// 	__builtin_printf("%s", get_next_line(fd[2]));
// 	__builtin_printf("%s", get_next_line(fd[2]));
// 	__builtin_printf("\n2 lines file1:\n");
// 	__builtin_printf("%s", get_next_line(fd[0]));
// 	__builtin_printf("%s", get_next_line(fd[0]));
// 	__builtin_printf("\n1 line file2:\n");
// 	__builtin_printf("%s", get_next_line(fd[1]));
// 	__builtin_printf("\n2 lines file1:\n");
// 	__builtin_printf("%s", get_next_line(fd[0]));
// 	__builtin_printf("%s", get_next_line(fd[0]));
// 	__builtin_printf("\n2 line file2:\n");
// 	__builtin_printf("%s", get_next_line(fd[1]));
// 	__builtin_printf("%s", get_next_line(fd[1]));
// 	// __builtin_printf("\n2 lines file5:\n");
// 	// __builtin_printf("%s", get_next_line(-1));
// 	// __builtin_printf("%s", get_next_line(-1));
// 	// __builtin_printf("\n2 l standard:\n");
// 	// __builtin_printf("%s", get_next_line(0));
// 	// __builtin_printf("%s", get_next_line(0));
// // 	while (line = get_next_line(fd[3]))
// // 		__builtin_printf("%d:      %s", i++, line);
// 	close(fd[0]);
// 	close(fd[1]);
// 	close(fd[2]);
// 	close(fd[3]);
// }
