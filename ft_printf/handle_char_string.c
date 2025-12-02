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

	s = va_arg(args, char *);
	if (!s)
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
