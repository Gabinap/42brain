/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:51:03 by gagulhon          #+#    #+#             */
/*   Updated: 2025/12/02 10:51:04 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_hex(t_format *fmt, va_list args, int uppercase)
{
	unsigned int	num;
	char			*hex_str;
	int				count;

	num = va_arg(args, unsigned int);
	if (fmt->precision == 0 && num == 0)
	{
		if (fmt->width > 0)
			return (print_padding(fmt->width, ' '));
		return (0);
	}
	hex_str = ft_xtoa(num, uppercase);
	if (!hex_str)
		return (0);
	count = print_hex_format(fmt, hex_str, num);
	free(hex_str);
	return (count);
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
		count += write(1, "0x0", 3);
		if (fmt->width > 3)
		{
			if (fmt->minus)
				count += print_padding(fmt->width - 3, ' ');
		}
		return (count);
	}
	count += write(1, "0x", 2);
	hex_str = ft_xtoa(addr, 0);
	if (!hex_str)
		return (count);
	count += write(1, hex_str, ft_strlen(hex_str));
	free(hex_str);
	return (count);
}
