/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 19:07:38 by gagulhon          #+#    #+#             */
/*   Updated: 2025/12/03 12:26:52 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static void	ft_memcpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	if (n == 0 || !dst || !src)
		return ;
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*ft_strjoin_free(char *s1, char *s2, ssize_t len2)
{
	char	*result;
	size_t	len1;

	if (!s2)
		return (NULL);
	len1 = ft_strlen(s1);
	result = malloc(len1 + len2 + 1);
	if (!result)
	{
		free(s1);
		s1 = NULL;
		return (NULL);
	}
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	free(s1);
	s1 = NULL;
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		sub = malloc(1);
		if (sub)
			sub[0] = '\0';
		return (sub);
	}
	else if (len > s_len - start)
		len = s_len - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
