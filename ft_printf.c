/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:22:49 by gagulhon          #+#    #+#             */
/*   Updated: 2025/11/30 20:05:12 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr_fd(unsigned int n, int fd)
{
	char	c;
	int		count;

	count = 0;
	while (n > 0)
	{
		c = (n % 10) + 48;
		write(fd, &c, 1);
		n = n / 10;
		count++;
	}
	return (count);
}

int	print_hex(unsigned long nb, int format)
{
	char	buffer[17];
	char	*base;
	int		i;
	int		count;

	if (format == 0)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	i = 0;
	if (nb == 0)
		buffer[i++] = '0';
	while (nb > 0)
	{
		buffer[i++] = base[nb % 16];
		nb /= 16;
	}
	count = i;
	while (i > 0)
		write(1, &buffer[--i], 1);
	return (count);
}

int	print_pointer(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (write(1, "0x0", 3));
	count += write(1, "0x", 2);
	count += print_hex((unsigned long)ptr, 0);
	return (count);
}

int	handle_convertion(char c, va_list args)
{
	char	ch;

	if (c == 'c')
	{
		ch = (char)va_arg(args, int);
		return (write(1, &ch, 1));
	}
	if (c == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	if (c == 'p')
		return (print_pointer(va_arg(args, void *)));
	if (c == '%')
		return (write(1, "%", 1));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (c == 'u')
		return (ft_putunbr_fd(va_arg(args, unsigned int), 1));
	if (c == 'x')
		return (print_hex(va_arg(args, unsigned int), 0));
	if (c == 'X')
		return (print_hex(va_arg(args, unsigned int), 1));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		count;

	count = 0;
	if (!s)
		s = "(null)";
	va_start(args, s);
	while (*s != '\0')
	{
		if (*s == '%')
		{
			s++;
			if (*s == '\n')
				break ;
			count += handle_convertion(*s, args);
		}
		else
		{
			write(1, s, 1);
			count++;
		}
		s++;
	}
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	int	i = 9;
// 	unsigned int u = 88;
// 	int nb = 897;
// 	ft_printf("my ft_printf:\n");
// 	ft_printf("teeeest %c %%%s%p\nid%i%d\n%u\n%x%X", 'c', "string", &i, i, i, u, nb, nb);
// 	__builtin_printf("\n\nreal printf:\n");
// 	__builtin_printf("teeeest %c %%%s%p\nid%i%d\n%u\n%x%X", 'c', "string", &i, i, i, u, nb, nb);
// 	return (0);
// }
