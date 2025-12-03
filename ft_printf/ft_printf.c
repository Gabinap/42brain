/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:50:51 by gagulhon          #+#    #+#             */
/*   Updated: 2025/12/03 12:29:44 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_format(t_format *fmt, va_list args)
{
	if (fmt->specifier == 'c')
		return (handle_char(fmt, args));
	else if (fmt->specifier == 's')
		return (handle_string(fmt, args));
	else if (fmt->specifier == 'd' || fmt->specifier == 'i')
		return (handle_integer(fmt, args));
	else if (fmt->specifier == 'u')
		return (handle_unsigned(fmt, args));
	else if (fmt->specifier == 'x')
		return (handle_hex(fmt, args, 0));
	else if (fmt->specifier == 'X')
		return (handle_hex(fmt, args, 1));
	else if (fmt->specifier == 'p')
		return (handle_pointer(fmt, args));
	else if (fmt->specifier == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_format	fmt;
	int			count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format = parse_format(format, &fmt);
			count += handle_format(&fmt, args);
		}
		else if (*format != '%')
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}

// int main(void)
// {
// // 	ft_printf("count=%-5d", ft_printf("%%"));
// // 	__builtin_printf("count=%-5d", __builtin_printf("%%"));
// // 	ft_printf("\ncount=%-5d", ft_printf("%-100.10s", "Hello world."));
// // 	__builtin_printf("\ncount=%-5d", __builtin_printf("%-100.10s", "Hello world."));
// // 	ft_printf("\ncount=%-5d", ft_printf("%-10.100s", "Hello world."));
// // 	__builtin_printf("count=%-5d", __builtin_printf("%-10.100s", "Hello world."));
// 	ft_printf(".%-s.", "s");
// 	__builtin_printf("\n.%-s.", "s");
// }
