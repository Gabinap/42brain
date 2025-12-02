/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:51:09 by gagulhon          #+#    #+#             */
/*   Updated: 2025/12/02 10:51:10 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_prefix(int uppercase, unsigned int num, t_format *fmt)
{
	if (!fmt->hash || num == 0)
		return (0);
	if (uppercase)
		return (write(1, "0X", 2));
	else
		return (write(1, "0x", 2));
}

int	print_hex_format(t_format *fmt, char *hex, unsigned int num)
{
	int	len;
	int	prefix_len;
	int	zeros;
	int	spaces;
	int	count;

	len = ft_strlen(hex);
	prefix_len = 0;
	if (fmt->hash && num != 0)
		prefix_len = 2;
	zeros = 0;
	if (fmt->precision > len)
		zeros = fmt->precision - len;
	spaces = 0;
	if (fmt->width > (prefix_len + zeros + len))
		spaces = fmt->width - (prefix_len + zeros + len);
	count = 0;
	if (!fmt->minus && !fmt->zero)
		count += print_padding(spaces, ' ');
	count += print_prefix(fmt->specifier == 'X', num, fmt);
	if (!fmt->minus && fmt->zero && fmt->precision < 0)
		count += print_padding(spaces, '0');
	count += print_padding(zeros, '0');
	count += write(1, hex, len);
	if (fmt->minus)
		count += print_padding(spaces, ' ');
	return (count);
}
