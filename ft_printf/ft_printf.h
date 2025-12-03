/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:51:00 by gagulhon          #+#    #+#             */
/*   Updated: 2025/12/03 07:28:56 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_format
{
	int		width;
	int		precision;
	int		minus;
	int		zero;
	int		hash;
	int		plus;
	int		space;
	char	specifier;
}	t_format;

int			ft_printf(const char *format, ...);
const char	*parse_format(const char *s, t_format *fmt);

int			handle_char(t_format *fmt, va_list args);
int			handle_string(t_format *fmt, va_list args);

int			handle_integer(t_format *fmt, va_list args);
int			handle_unsigned(t_format *fmt, va_list args);

int			handle_hex(t_format *fmt, va_list args, int uppercase);
int			handle_pointer(t_format *fmt, va_list args);

int			print_padding(int count, char pad);
int			ft_strlen(const char *s);
char		*ft_itoa(int n);
char		*ft_utoa(unsigned int n);
char		*ft_xtoa(unsigned long n, int uppercase);

int			print_number(t_format *fmt, char *num, int neg);
int			print_hex_format(t_format *fmt, char *hex, unsigned int num);
int			get_num_len(long n);
int			get_unum_len(unsigned long n);

#endif
