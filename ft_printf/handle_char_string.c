/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:50:56 by gagulhon          #+#    #+#             */
/*   Updated: 2025/12/03 13:56:37 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_char(t_format *fmt, va_list args)
{
	char	c;
	int		count;

	c = (char)va_arg(args, int);
	count = 0;
	if (!fmt->minus && fmt->width > 1)
		count += print_padding(fmt->width - 1, ' ');
	count += write(1, &c, 1);
	if (fmt->minus && fmt->width > 1)
		count += print_padding(fmt->width - 1, ' ');
	return (count);
}

static int	get_print_len(char *s, t_format *fmt)
{
	int	len;

	len = ft_strlen(s);
	if (fmt->precision >= 0 && fmt->precision < len)
		return (fmt->precision);
	return (len);
}

int	handle_string(t_format *fmt, va_list args)
{
	char	*s;
	int		len;
	int		count;
	int		is_s;

	is_s = 1;
	s = va_arg(args, char *);
	if (!s)
		is_s = 0;
	if (!s && (fmt->precision < 6 && fmt->precision > 0))
		s = "";
	else if (!s)
		s = "(null)";
	len = get_print_len(s, fmt);
	count = 0;
	if (!fmt->minus && fmt->width > len)
		count += print_padding(fmt->width - len, ' ');
	count += write(1, s, len);
	if (fmt->minus && fmt->width > len)
		count += print_padding(fmt->width - len, ' ');
	return (count);
}
