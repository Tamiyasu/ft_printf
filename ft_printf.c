/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:42:55 by tmurakam          #+#    #+#             */
/*   Updated: 2020/07/30 02:05:51 by tmurakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format_str, ...)
{
	va_list	arg_list;
	int		char_count;

	char_count = 0;
	va_start(arg_list, format_str);
	while(*format_str)
	{
		if(*format_str != '%')
			char_count += write(1, format_str++, 1);
		else
			format_write((char **)&format_str, &char_count, arg_list);
	}
	va_end(arg_list);
	return (char_count);
}

void init_t_parsed_fmt(t_parsed_fmt *s_parsed_fmt)
{
	s_parsed_fmt->conversion_spec = '\0';
	s_parsed_fmt->field_width = 0;
	s_parsed_fmt->flag = 0;
	s_parsed_fmt->precision = INT_MAX;
}

void read_flag(char **format_str, t_parsed_fmt *parsed_fmt)
{
	while (**format_str && ft_strchr("-+ 0#", **format_str))
	{
		if (**format_str == '-')
			parsed_fmt->flag |= F_MINUS;
		else if (**format_str == '+')
			parsed_fmt->flag |= F_PLUS;
		else if (**format_str == ' ')
			parsed_fmt->flag |= F_SPACE;
		else if (**format_str == '0')
			parsed_fmt->flag |= F_ZERO;
		else if (**format_str == '#')
			parsed_fmt->flag |= F_SHARP;
		(*format_str)++;
	}
}

void read_int_in_format(char **format_str, char *chr_str, int *i)
{
	while (**format_str && ft_strchr(chr_str, **format_str))
	{
		if('0' <= **format_str && **format_str <= '9' && *i != -1)
			*i = *i * 10 + (**format_str - '0');
		else if(**format_str == '.')
			*i = 0;
		else
			*i = -1;
		(*format_str)++;
	}
}

void format_purser(char **format_str, t_parsed_fmt *parsed_fmt)
{
	read_flag(format_str, parsed_fmt);
	read_int_in_format(format_str, "0123456789*", &(parsed_fmt->field_width));
	read_int_in_format(format_str, "0123456789*.", &(parsed_fmt->precision));
	while (**format_str && ft_strchr("hlL", **format_str))
		(*format_str)++;
	parsed_fmt->conversion_spec = **format_str;
	if (**format_str)
		(*format_str)++;
}

int format_write(char **format_str, int *char_count, va_list arg_list)
{
	t_parsed_fmt	parsed_fmt;
	int		char_count_in_format;

	char_count_in_format = 0;
	char_count_in_format++;
	(*format_str)++;
	init_t_parsed_fmt(&parsed_fmt);
	format_purser(format_str, &parsed_fmt);
	if (parsed_fmt.conversion_spec == 's')
		write_s(&parsed_fmt, char_count, arg_list);
	else if (parsed_fmt.conversion_spec == 'd')
		write_d(&parsed_fmt, char_count, arg_list);
	else if (parsed_fmt.conversion_spec == 'u' || parsed_fmt.conversion_spec == 'i' ||
			 parsed_fmt.conversion_spec == 'x' || parsed_fmt.conversion_spec == 'X' ||
			 parsed_fmt.conversion_spec == 'o')
		write_u(&parsed_fmt, char_count, arg_list);
	else if (parsed_fmt.conversion_spec == 'c' || parsed_fmt.conversion_spec == '%')
		write_c(&parsed_fmt, char_count, arg_list);
	return (1);	
}

char	*ft_utoax(unsigned int n, t_parsed_fmt *parsed_fmt, int base)
{
	char	*return_s;
	int		order;
	int		i;
	int		n_copy;
	char	base_origin_10;

	base_origin_10 = 'a';
	if (parsed_fmt->conversion_spec == 'X')
		base_origin_10 = 'A';
	if (n == 0 && parsed_fmt->precision == 0)
		return (ft_calloc(1, 1));
	if (parsed_fmt->precision == INT_MAX)
		parsed_fmt->precision = 0;
	n_copy = n;
	order = 1;
	while (n_copy /= base)
		order++;
	order = MAX(order, parsed_fmt->precision);
	if(!(return_s = ft_calloc(order + 1, sizeof(char))))
		return (return_s);
	ft_memset(return_s, '0', order);
	*(return_s + order) = '\0';
	i = 0;
	while (n)
	{
		*(return_s + order - ++i) = ABS(n % base) + (ABS(n % base) < 10 ? '0' : base_origin_10 - 10);
		n /= base;
	}
	return (return_s);
}

char	*ft_itoax(int n, t_parsed_fmt *parsed_fmt, int base)
{
	char	*return_s;
	int		order;
	int		i;
	int		n_copy;

	if (n == 0 && parsed_fmt->precision == 0)
	{
		return (ft_calloc(1, 1));
	}
	if (parsed_fmt->precision == INT_MAX)
		parsed_fmt->precision = 0;
	n_copy = n;
	order = 1;
	while (n_copy /= base)
		order++;
	order = MAX(order, parsed_fmt->precision) + (n < 0 ? 1 : 0);
	if(!(return_s = ft_calloc(order + 1, sizeof(char))))
		return (return_s);
	ft_memset(return_s, '0', order);
	*(return_s + order) = '\0';
	if(n < 0)
		*(return_s) = '-';
	i = 0;
	while (n)
	{
		*(return_s + order - ++i) = ABS(n % base) + (ABS(n % base) < 10 ? '0' : 'a' - 10);
		n /= base;
	}
	return (return_s);
}

char	*ft_strchr(const char *s, int c)
{
	char *i_p;

	i_p = (char *)s;
	while (*i_p != 0 && *i_p != c)
		i_p++;
	if (*i_p != c)
		i_p = 0;
	return (i_p);
}

int	ft_putstr(char *s, size_t len)
{
	return (write(1, s, len));
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*(s + i) != 0)
		i++;
	return (i);
}

int	ft_putnbr_fd(int n, int fd)
{
	int count;

	count = 0;
	if (n / 10)
		count += ft_putnbr_fd(n / 10, fd);
	else
	{
		if (n < 0)
			count += ft_putchar_fd('-', fd);
	}
	count += ft_putchar_fd('0' + (n % 10) * ((0 < n) ? 1 : -1), fd);
	return (count);
}

int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*return_p;

	return_p = malloc(count * size);
	if (return_p)
		ft_bzero(return_p, count * size);
	return ((void *)return_p);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
		*((unsigned char*)b + i++) = (unsigned char)c;
	return (b);
}


void write_c(t_parsed_fmt *parsed_fmt, int *char_count, va_list arg_list)
{
	int		i;
	char	c;
	char	fill_c;

	fill_c = ' ';
	if (parsed_fmt->conversion_spec == '%')
		c = '%';
	else
		c = va_arg(arg_list, int);
	if (parsed_fmt->flag & F_ZERO && !(parsed_fmt->flag & F_MINUS))
		fill_c = '0';
	if (parsed_fmt->flag & F_MINUS)
		*char_count += ft_putchar_fd(c, 1);
	i = 0;
	while (i++ < parsed_fmt->field_width - 1)
		*char_count += ft_putchar_fd(fill_c, 1);
	if (!(parsed_fmt->flag & F_MINUS))
		*char_count += ft_putchar_fd(c, 1);
}

void write_s(t_parsed_fmt *parsed_fmt, int *char_count, va_list arg_list)
{
	int i;
	char fill_c;
	char *str;

	str = va_arg(arg_list, char*);
	if(!str)
		str = "(null)";
	fill_c = ' ';
	if (parsed_fmt->flag & F_ZERO && !(parsed_fmt->flag & F_MINUS))
		fill_c = '0';
	if (parsed_fmt->flag & F_MINUS)
		*char_count += ft_putstr(str, MIN(parsed_fmt->precision, (int)ft_strlen(str)));
	i = 0;
	while (i++ < (int)parsed_fmt->field_width - MIN(parsed_fmt->precision, (int)ft_strlen(str)))
		*char_count += ft_putchar_fd(fill_c, 1);
	if (!(parsed_fmt->flag & F_MINUS))
		*char_count += ft_putstr(str, MIN(parsed_fmt->precision, (int)ft_strlen(str)));
}

void write_d(t_parsed_fmt *parsed_fmt, int *char_count, va_list arg_list)
{
	int i;
	int d;
	char fill_c;
	char *str;
	int base;

	base = 10;
	if (parsed_fmt->conversion_spec == 'x' || parsed_fmt->conversion_spec == 'X')
		base = 16;
	if (parsed_fmt->conversion_spec == 'o')
		base = 8;
	d = va_arg(arg_list, int);
	if (parsed_fmt->flag & F_ZERO && parsed_fmt->precision == INT_MAX)
		parsed_fmt->precision = parsed_fmt->field_width - (d < 0 ? 1 : 0);
	else if (parsed_fmt->flag & F_ZERO && !(parsed_fmt->flag & F_MINUS) && parsed_fmt->precision == INT_MAX)
		fill_c = '0';
	str = ft_itoax(d, parsed_fmt, base);
	if(!str)
		str = "(null)";
	fill_c = ' ';
	if (parsed_fmt->flag & F_MINUS)
	{
		i = 0;
		while (i++ < parsed_fmt->precision - (int)ft_strlen(str))
			*char_count += ft_putchar_fd('0', 1);
		*char_count += ft_putstr(str, (int)ft_strlen(str));
	}
	i = 0;
	while (i++ < (int)parsed_fmt->field_width - MAX(parsed_fmt->precision, (int)ft_strlen(str)))
		*char_count += ft_putchar_fd(fill_c, 1);
	if (!(parsed_fmt->flag & F_MINUS))
	{
		i = 0;
		while (i++ < parsed_fmt->precision - (int)ft_strlen(str))
			*char_count += ft_putchar_fd('0', 1);
		*char_count += ft_putstr(str, (int)ft_strlen(str));
	}
	free(str);
}

void write_u(t_parsed_fmt *parsed_fmt, int *char_count, va_list arg_list)
{
	int i;
	unsigned int u;
	char fill_c;
	char *str;
	int base;

	base = 10;
	u = va_arg(arg_list, unsigned int);
	if (parsed_fmt->flag & F_ZERO && parsed_fmt->precision == INT_MAX)
		parsed_fmt->precision = parsed_fmt->field_width;
	else if (parsed_fmt->flag & F_ZERO && !(parsed_fmt->flag & F_MINUS) && parsed_fmt->precision == INT_MAX)
		fill_c = '0';
	str = ft_itoax(u, parsed_fmt, base);
	if(!str)
		str = "(null)";
	fill_c = ' ';
	if (parsed_fmt->flag & F_MINUS)
	{
		i = 0;
		while (i++ < parsed_fmt->precision - (int)ft_strlen(str))
			*char_count += ft_putchar_fd('0', 1);
		*char_count += ft_putstr(str, (int)ft_strlen(str));
	}
	i = 0;
	while (i++ < (int)parsed_fmt->field_width - MAX(parsed_fmt->precision, (int)ft_strlen(str)))
		*char_count += ft_putchar_fd(fill_c, 1);
	if (!(parsed_fmt->flag & F_MINUS))
	{
		i = 0;
		while (i++ < parsed_fmt->precision - (int)ft_strlen(str))
			*char_count += ft_putchar_fd('0', 1);
		*char_count += ft_putstr(str, (int)ft_strlen(str));
	}
	free(str);
}