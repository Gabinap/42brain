/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:51:10 by gagulhon          #+#    #+#             */
/*   Updated: 2025/12/04 08:06:33 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_sign_len(t_format *fmt, int is_negative)
{
	if (is_negative || fmt->plus || fmt->space)
		return (1);
	return (0);
}

static void	print_sign(t_format *fmt, int is_negative, int *count)
{
	if (is_negative)
		*count += write(1, "-", 1);
	else if (fmt->plus)
		*count += write(1, "+", 1);
	else if (fmt->space)
		*count += write(1, " ", 1);
}

static int	calculate_padding(t_format *fmt, int len, int sign, int zeros)
{
	int	total_len;

	total_len = sign + zeros + len;
	if (fmt->width > total_len)
		return (fmt->width - total_len);
	return (0);
}

static int	print_number_init_len(char **num, int is_negative)
{
	int	len;

	len = ft_strlen(*num);
	if (is_negative && *(num[0]) == '-')
	{
		(*num)++;
		len--;
	}
	return (len);
}

int	print_number(t_format *fmt, char *num, int is_negative)
{
	int	len;
	int	sign_len;
	int	zeros;
	int	spaces;
	int	count;

	len = print_number_init_len(&num, is_negative);
	sign_len = get_sign_len(fmt, is_negative);
	zeros = 0;
	if (fmt->precision > len)
		zeros = fmt->precision - len;
	spaces = calculate_padding(fmt, len, sign_len, zeros);
	count = 0;
	if (!fmt->minus && (!fmt->zero || fmt->precision >= 0))
		count += print_padding(spaces, ' ');
	print_sign(fmt, is_negative, &count);
	if (!fmt->minus && fmt->zero && fmt->precision < 0)
		count += print_padding(spaces, '0');
	count += print_padding(zeros, '0');
	count += write(1, num, len);
	if (fmt->minus)
		count += print_padding(spaces, ' ');
	return (count);
}
