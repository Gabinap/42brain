/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_numbers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:51:04 by gagulhon          #+#    #+#             */
/*   Updated: 2025/12/03 07:15:00 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_integer(t_format *fmt, va_list args)
{
	int		num;
	char	*num_str;
	int		count;

	num = va_arg(args, int);
	if (fmt->precision == 0 && num == 0)
	{
		if (fmt->width > 0)
			return (print_padding(fmt->width, ' '));
		return (0);
	}
	num_str = ft_itoa(num);
	if (!num_str)
		return (0);
	count = 0;
	count += print_number(fmt, num_str, num < 0);
	free(num_str);
	return (count);
}

int	handle_unsigned(t_format *fmt, va_list args)
{
	unsigned int	num;
	char			*num_str;
	int				count;

	num = va_arg(args, unsigned int);
	if (fmt->precision == 0 && num == 0)
	{
		if (fmt->width > 0)
			return (print_padding(fmt->width, ' '));
		return (0);
	}
	num_str = ft_utoa(num);
	if (!num_str)
		return (0);
	fmt->plus = 0;
	fmt->space = 0;
	count = print_number(fmt, num_str, 0);
	free(num_str);
	return (count);
}
