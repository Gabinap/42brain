/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:51:03 by gagulhon          #+#    #+#             */
/*   Updated: 2025/12/03 09:35:01 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_hex(t_format *fmt, va_list args, int uppercase)
{
	unsigned int	num;
	char			*hex_str;
	int				count;

	count = 0;
	num = va_arg(args, unsigned int);
	if (fmt->precision == 0 && num == 0)
	{
		if (fmt->width > 0)
			return (print_padding(fmt->width, ' '));
		return (count);
	}
	hex_str = ft_xtoa(num, uppercase);
	if (!hex_str)
		return (count);
	count = print_hex_format(fmt, hex_str, num);
	return (free(hex_str), count);
}

int	handle_pointer(t_format *fmt, va_list args)
{
	void			*ptr;
	char			*hex_str;
	int				count;
	unsigned long	addr;

	ptr = va_arg(args, void *);
	addr = (unsigned long)ptr;
	count = 0;
	if (!ptr)
	{
		if (fmt->width > 5 && !fmt->minus)
			count += print_padding(fmt->width - 5, ' ');
		count += write(1, "(nil)", 5);
		if (fmt->width > 5 && fmt->minus)
			count += print_padding(fmt->width - 5, ' ');
		return (count);
	}
	hex_str = ft_xtoa(addr, 0);
	if (!hex_str)
		return (count);
	if (fmt->width > ft_strlen(hex_str) && !fmt->minus)
		count += print_padding(fmt->width - ft_strlen(hex_str) - 2, ' ');
	count += write(1, "0x", 2);
	count += write(1, hex_str, ft_strlen(hex_str));
	if (fmt->width > ft_strlen(hex_str) && fmt->minus)
		count += print_padding(fmt->width - ft_strlen(hex_str) - 2, ' ');
	return (free(hex_str), count);
}
