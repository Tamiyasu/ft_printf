/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:42:55 by tmurakam          #+#    #+#             */
/*   Updated: 2020/07/28 23:17:29 by tmurakam         ###   ########.fr       */
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

void format_purser(char **format_str, t_parsed_fmt *parsed_fmt, va_list arg_list)
{
	if (arg_list)
	{
		/*あとでけす むらかみたみやす*/
	}
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
	while (**format_str && ft_strchr("0123456789*", **format_str))
	{
		if('0' <= **format_str && **format_str <= '9' && parsed_fmt->field_width != -1)
		{
			parsed_fmt->field_width *= 10;
			parsed_fmt->field_width += **format_str - '0';
		}
		else
		{
			parsed_fmt->field_width = -1;
		}
		(*format_str)++;
	}
	while (**format_str && ft_strchr("0123456789*.", **format_str))
	{
		if('0' <= **format_str && **format_str <= '9' && parsed_fmt->precision != -1)
		{
			parsed_fmt->precision *= 10;
			parsed_fmt->precision += **format_str - '0';
			(*format_str)++;
		}
		else if (**format_str == '*')
		{
			parsed_fmt->precision = -1;
			(*format_str)++;
		}
		else
		{
			parsed_fmt->precision = 0;
			(*format_str)++;
		}
	}
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
	char *str;
	int d;
	int i;
	char fill_c;

	char_count_in_format = 0;
	char_count_in_format++;
	(*format_str)++;
	init_t_parsed_fmt(&parsed_fmt);
	format_purser(format_str, &parsed_fmt, arg_list);
	if (parsed_fmt.conversion_spec == 's')
	{
//		printf("pres : %d\n", parsed_fmt.precision);
		i = 0;
		fill_c = ' ';
		str = va_arg(arg_list, char*);
		if(!str)
			str = "(null)";
		if (parsed_fmt.flag & F_ZERO && !(parsed_fmt.flag & F_MINUS))
			fill_c = '0';
		if (parsed_fmt.flag & F_MINUS)
			*char_count += ft_putstr(str, MIN(parsed_fmt.precision, (int)ft_strlen(str)));
		while (i++ < (int)parsed_fmt.field_width - MIN(parsed_fmt.precision, (int)ft_strlen(str)))
			*char_count += ft_putchar_fd(fill_c, 1);
		if (!(parsed_fmt.flag & F_MINUS))
			*char_count += ft_putstr(str, MIN(parsed_fmt.precision, (int)ft_strlen(str)));
	}
	else if (parsed_fmt.conversion_spec == 'd')
	{
		d = va_arg(arg_list, int);
		*char_count += ft_putnbr_fd(d, 1);
	}
	else if (parsed_fmt.conversion_spec == 'c')
		write_c(&parsed_fmt, char_count, arg_list);
	else if (parsed_fmt.conversion_spec == '%')
	{
//		printf("\nparsed_fmt.field_width : %d\n", parsed_fmt.field_width);
//		printf("\nparsed_fmt.flag : %d\n", parsed_fmt.flag);
		i = 0;
		fill_c = ' ';
		if (parsed_fmt.flag & F_ZERO && !(parsed_fmt.flag & F_MINUS))
			fill_c = '0';
		if (parsed_fmt.flag & F_MINUS)
			*char_count += ft_putchar_fd('%', 1);
		while (i++ < parsed_fmt.field_width - 1)
			*char_count += ft_putchar_fd(fill_c, 1);
		if (!(parsed_fmt.flag & F_MINUS))
			*char_count += ft_putchar_fd('%', 1);
	}
	return (1);	
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

void write_c(t_parsed_fmt *parsed_fmt, int *char_count, va_list arg_list)
{
	int		i;
	char	c;
	char	fill_c;

	i = 0;
	c = va_arg(arg_list, int);
	fill_c = ' ';
	if (parsed_fmt->flag & F_ZERO && !(parsed_fmt->flag & F_MINUS))
		fill_c = '0';
	if (parsed_fmt->flag & F_MINUS)
		*char_count += ft_putchar_fd(c, 1);
	while (i++ < parsed_fmt->field_width - 1)
		*char_count += ft_putchar_fd(fill_c, 1);
	if (!(parsed_fmt->flag & F_MINUS))
		*char_count += ft_putchar_fd(c, 1);
}

