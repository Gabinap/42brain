/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:07:29 by gagulhon          #+#    #+#             */
/*   Updated: 2025/11/26 15:25:22 by gagulhon         ###   ########.fr       */
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

	if (s == NULL)
		return (NULL);
	i = 0;
	c = (unsigned char)c;
	while (s[i] != c && s[i])
		i++;
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

static void	remove_fd_from_list(t_list_fd **head, int fd)
{
	t_list_fd	*current;
	t_list_fd	*prev;
	t_list_fd	*to_free;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			to_free = current;
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			if (to_free->contain)
				free(to_free->contain);
			free(to_free);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

char	*get_next_line(int fd)
{
	static t_list_fd	*head = NULL;
	t_list_fd			*actual;
	char				*buffer;
	int					byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
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
	if (actual == NULL)
	{
		free(buffer);
		return (NULL);
	}
	byte_read = 1;
	while (!ft_strchr(actual->contain, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			free(actual->contain);
			actual->contain = NULL;
			return (NULL);
		}
		if (byte_read == 0)
			break ;
		buffer[byte_read] = '\0';
		actual->contain = ft_strjoin_and_free(actual->contain, buffer);
		if (actual->contain == NULL)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	if (actual->contain && actual->contain[0] != '\0')
		return (str_new_strline_and_free(&(actual->contain)));
	if (actual->contain)
	{
	    free(actual->contain);
	    actual->contain = NULL;
	}
	if (byte_read == 0 && actual->contain == NULL)
    	remove_fd_from_list(&head, fd);
	return (NULL);
}

// #include <fcntl.h>
// int main(void)
// {
// 	int fd[4];
// 	// int i = 1;

// 	fd[0] = open("file1", O_RDONLY);
// 	fd[1] = open("file2", O_RDONLY);
// 	fd[2] = open("file3", O_RDONLY);
// 	fd[3] = open("file4", O_RDONLY);
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
// 	__builtin_printf("\n1 line file2:\n");
// 	__builtin_printf("%s", get_next_line(fd[1]));
// // 	// __builtin_printf("\n2 lines file5:\n");
// // 	// __builtin_printf("%s", get_next_line(-1));
// // 	// __builtin_printf("%s", get_next_line(-1));
// // 	// __builtin_printf("\n2 l standard:\n");
// // 	// __builtin_printf("%s", get_next_line(0));
// // 	// __builtin_printf("%s", get_next_line(0));
// // 	// while (i <= 3000000)
// // 	// 	__builtin_printf("%d:      %s", i++, get_next_line(fd[3]));
// 	close(fd[0]);
// 	close(fd[1]);
// 	close(fd[2]);
// 	close(fd[3]);
// }

// ne fonctionne pas avec des buffer plus grands que 1 & memleak
// cc -D BUFFER_SIZE=2 get_next_line.c get_next_line_utils.c && ./a.out
