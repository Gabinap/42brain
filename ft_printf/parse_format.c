#include "ft_printf.h"

void	init_format(t_format *fmt)
{
	fmt->width = 0;
	fmt->precision = -1;
	fmt->minus = 0;
	fmt->zero = 0;
	fmt->hash = 0;
	fmt->plus = 0;
	fmt->space = 0;
	fmt->specifier = 0;
}

const char	*parse_flags(const char *s, t_format *fmt)
{
	while (*s == '-' || *s == '0' || *s == '#' || *s == '+' || *s == ' ')
	{
		if (*s == '-')
			fmt->minus = 1;
		else if (*s == '0')
			fmt->zero = 1;
		else if (*s == '#')
			fmt->hash = 1;
		else if (*s == '+')
			fmt->plus = 1;
		else if (*s == ' ')
			fmt->space = 1;
		s++;
	}
	return (s);
}

const char	*parse_width(const char *s, t_format *fmt)
{
	fmt->width = 0;
	while (*s >= '0' && *s <= '9')
	{
		fmt->width = fmt->width * 10 + (*s - '0');
		s++;
	}
	return (s);
}

const char	*parse_precision(const char *s, t_format *fmt)
{
	if (*s == '.')
	{
		s++;
		fmt->precision = 0;
		while (*s >= '0' && *s <= '9')
		{
			fmt->precision = fmt->precision * 10 + (*s - '0');
			s++;
		}
	}
	return (s);
}

const char	*parse_format(const char *s, t_format *fmt)
{
	init_format(fmt);
	s++;
	s = parse_flags(s, fmt);
	s = parse_width(s, fmt);
	s = parse_precision(s, fmt);
	fmt->specifier = *s;
	if (fmt->minus)
		fmt->zero = 0;
	if (fmt->plus)
		fmt->space = 0;
	return (s);
}
