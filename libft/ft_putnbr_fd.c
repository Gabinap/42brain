/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:34:34 by gagulhon          #+#    #+#             */
/*   Updated: 2025/11/30 20:17:39 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		count;

	count = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		count++;
	}
	while (n > 0)
	{
		c = (n % 10) + 48;
		write(fd, &c, 1);
		n = n / 10;
		count++;
	}
	return (count);
}
