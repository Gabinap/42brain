/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 19:07:38 by gagulhon          #+#    #+#             */
/*   Updated: 2025/11/23 16:04:37 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(const char *s)
{
	int	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (*s++)
		len++;
	return (len);
}

static size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dest;
	size_t	len_src;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	i = 0;
	if (size <= len_dest)
		return (size + len_src);
	while ((len_dest + i + 1 < size) && src[i])
	{
		dest[i + len_dest] = src[i];
		i++;
	}
	dest[len_dest + i] = 0;
	return (len_src + len_dest);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*str;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
	{
		str = malloc(sizeof(char) * (ft_strlen(s2) + 1));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		ft_strlcat(str, s2, ft_strlen(s2) + 1);
		return (str);
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc((sizeof(char)) * (len_s1 + len_s2 + 1));
	if (str == NULL)
	{
		free(s1);
		return (NULL);
	}
	str[0] = '\0';
	ft_strlcat(str, s1, len_s1 + 1);
	ft_strlcat(str, s2, len_s2 + len_s1 + 1);
	free((void *)s1);
	return (str);
}

static char	*keep_str_withoutline_and_returnline(char **str, char **line, int i)
{
	char	*temp;
	int		j;

	if ((*str)[i] == '\n')
	{
		temp = malloc(sizeof(char) * (ft_strlen(&(*str)[i + 1]) + 1));
		if (temp == NULL)
		{
			free(*line);
			return (NULL);
		}
		j = -1;
		while ((*str)[i + j++ + 1])
			temp[j] = (*str)[i + j + 1];
		free(*str);
		*str = temp;
	}
	else
	{
		free(*str);
		*str = NULL;
	}
	return (*line);
}

//may be change the return who are not opti
char	*str_new_strline_and_free(char **str)
{
	char	*line;
	int		i;
	int		j;

	if (str == NULL || *str == NULL)
		return (NULL);
	i = 0;
	while ((*str)[i] && (*str)[i - 1] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	if (i == 0)
		return (NULL);
	line[i] = '\0';
	j = i - 1;
	while (j >= 0)
	{
		line[j] = (*str)[j];
		j--;
	}
	return (keep_str_withoutline_and_returnline(str, &line, i));
}
