/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:42:45 by gagulhon          #+#    #+#             */
/*   Updated: 2025/11/26 12:30:39 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list_fd
{
	int					fd;
	char				*contain;
	struct s_list_fd	*next;
}				t_list_fd;
char	*ft_strjoin_and_free(char *s1, char *s2);
char	*str_new_strline_and_free(char **str);
char 	*get_next_line(int fd);
#endif
