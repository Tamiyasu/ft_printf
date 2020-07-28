/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:42:55 by tmurakam          #+#    #+#             */
/*   Updated: 2020/07/28 20:12:36 by tmurakam         ###   ########.fr       */
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

void init_t_pursed_fmt(t_pursed_fmt *s_pursed_fmt)
{
	s_pursed_fmt->conversion_spec = '\0';
	s_pursed_fmt->field_width = 0;
	s_pursed_fmt->flag = 0;
	s_pursed_fmt->precision = 0;
}

void format_purser(char **format_str, t_pursed_fmt *pursed_fmt, va_list arg_list)
{
	if (arg_list)
	{
		
	}
	while (ft_strchr("-+ 0#", **format_str))
	{
		if (**format_str == '-')
		{
			pursed_fmt->flag |= F_MINUS;
//			printf ("minus_ '%d' \n", pursed_fmt->flag);
		}
		else if (**format_str == '+')
		{
			pursed_fmt->flag |= F_PLUS;
//			printf ("plus_\n");
		}
		else if (**format_str == ' ')
		{
			pursed_fmt->flag |= F_SPACE;
//			printf ("space_\n");
		}
		else if (**format_str == '0')
		{
			pursed_fmt->flag |= F_ZERO;
//			printf ("zero_\n");
		}
		else if (**format_str == '#')
		{
			pursed_fmt->flag |= F_SHARP;
//			printf ("sharp_\n");
		}
		(*format_str)++;
	}
	while (ft_strchr("0123456789*", **format_str))
	{
		if('0' <= **format_str && **format_str <= '9' && pursed_fmt->field_width != -1)
		{
			pursed_fmt->field_width *= 10;
			pursed_fmt->field_width += **format_str - '0';
			(*format_str)++;
		}
		else
		{
			pursed_fmt->field_width = -1;
			(*format_str)++;
		}
	}
	while (ft_strchr("0123456789*.", **format_str))
		(*format_str)++;
	while (ft_strchr("hlL", **format_str))
		(*format_str)++;
	pursed_fmt->conversion_spec = *(*format_str)++;
}


int format_write(char **format_str, int *char_count, va_list arg_list)
{
	t_pursed_fmt	pursed_fmt;
	int		char_count_in_format;
	char *str;
	int d;
	int i;
	char fill_c;

	char_count_in_format = 0;
	char_count_in_format++;
	(*format_str)++;
	init_t_pursed_fmt(&pursed_fmt);
	format_purser(format_str, &pursed_fmt, arg_list);
	if (pursed_fmt.conversion_spec == 's')
	{
		str = va_arg(arg_list, char*);
		*char_count += ft_putstr(str);
	}
	else if (pursed_fmt.conversion_spec == 'd')
	{
		d = va_arg(arg_list, int);
		*char_count += ft_putnbr_fd(d, 1);
	}
	else if (pursed_fmt.conversion_spec == '%')
	{
//		printf("\npursed_fmt.field_width : %d\n", pursed_fmt.field_width);
//		printf("\npursed_fmt.flag : %d\n", pursed_fmt.flag);

		i = 0;
		fill_c = ' ';
		if (pursed_fmt.flag & F_ZERO && !(pursed_fmt.flag & F_MINUS))
			fill_c = '0';
		if (pursed_fmt.flag & F_MINUS)
			*char_count += ft_putchar_fd('%', 1);
		while (i++ < pursed_fmt.field_width - 1)
			*char_count += ft_putchar_fd(fill_c, 1);
		if (!(pursed_fmt.flag & F_MINUS))
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

int	ft_putstr(char *s)
{
	return (write(1, s, ft_strlen(s)));
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
