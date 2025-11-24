/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:07:29 by gagulhon          #+#    #+#             */
/*   Updated: 2025/11/24 17:35:34 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list_fd	*new_actual(t_list_fd **head, int fd)
{
	t_list_fd	*new_node;
	t_list_fd	*current;

	if (*head == NULL)
	{
		*head = malloc(sizeof(t_list_fd));
		if (*head == NULL)
			return (NULL);
		(*head)->fd = fd;
		(*head)->contain = NULL;
		(*head)->next = NULL;
		return (*head);
	}
	current = *head;
	while (current->next)
		current = current->next;
	new_node = malloc(sizeof(t_list_fd));
	if (new_node == NULL)
		return (NULL);
	current->next = new_node;
	new_node->fd = fd;
	new_node->contain = NULL;
	new_node->next = NULL;
	return (new_node);
}

static char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	c = (unsigned char)c;
	while (s[i] != c && s[i])
		i++;
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list_fd	*head = NULL;
	t_list_fd			*actual;
	char				*buffer;
	int					byte_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if ((fd < 0) || buffer == NULL)
		return (NULL);
	actual = head;
	while (actual)
	{
		if (actual->fd == fd)
			break ;
		actual = actual->next;
	}
	if (actual == NULL)
		actual = new_actual(&head, fd);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		actual->contain = ft_strjoin_and_free(actual->contain, buffer);
		if (actual->contain == NULL)
			return (NULL);
		if (ft_strchr(actual->contain, '\n'))
		{
			buffer = str_new_strline_and_free(&(actual->contain));
			if (buffer == NULL)
				return (NULL);
			return (buffer);
		}
	}
	free(buffer);
	return (NULL);
}

#include <fcntl.h>
int main(void)
{
	int fd[4];
	int i = 1;

	fd[0] = open("file1", O_RDONLY);
	fd[1] = open("file2", O_RDONLY);
	fd[2] = open("file3", O_RDONLY);
	fd[3] = open("file4", O_RDONLY);
	__builtin_printf("\n1 line file1:\n");
	__builtin_printf("%s", get_next_line(fd[0]));
	// __builtin_printf("\n2 lines file2:\n");
	// __builtin_printf("%s", get_next_line(fd[1]));
	// __builtin_printf("%s", get_next_line(fd[1]));
	// __builtin_printf("\n3 lines file3:\n");
	// __builtin_printf("%s", get_next_line(fd[2]));
	// __builtin_printf("%s", get_next_line(fd[2]));
	// __builtin_printf("%s", get_next_line(fd[2]));
	// __builtin_printf("\n2 lines file1:\n");
	// __builtin_printf("%s", get_next_line(fd[0]));
	// __builtin_printf("%s", get_next_line(fd[0]));
	// __builtin_printf("\n1 line file2:\n");
	// __builtin_printf("%s", get_next_line(fd[1]));
	// __builtin_printf("\n2 lines file1:\n");
	// __builtin_printf("%s", get_next_line(fd[0]));
	// __builtin_printf("%s", get_next_line(fd[0]));
	// __builtin_printf("\n1 line file2:\n");
	// __builtin_printf("%s", get_next_line(fd[1]));
	// __builtin_printf("\n2 lines file5:\n");
	// __builtin_printf("%s", get_next_line(-1));
	// __builtin_printf("%s", get_next_line(-1));
	// __builtin_printf("\n2 l standard:\n");
	// __builtin_printf("%s", get_next_line(0));
	// __builtin_printf("%s", get_next_line(0));
	// while (i <= 3000000)
	// 	__builtin_printf("%d:      %s", i++, get_next_line(fd[3]));
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
}
// ne fonctionne pas avec des buffer plus grands que 1
// cc -D BUFFER_SIZE=2 get_next_line.c get_next_line_utils.c && ./a.out
