/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_strformat.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:56:54 by tmurakam          #+#    #+#             */
/*   Updated: 2020/08/01 14:28:15 by tmurakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	read_flag(char **format_str, t_parsed_fmt *parsed_fmt)
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

void	read_hhll(char **format_str, t_parsed_fmt *parsed_fmt)
{
	if (**format_str && ft_strchr("hl", **format_str))
	{
		if (**format_str == 'h')
		{
			parsed_fmt->flag |= F_H;
			(*format_str)++;
			if (**format_str && ft_strchr("hl", **format_str))
			{
				parsed_fmt->flag |= F_HH;
				(*format_str)++;
			}
		}
		else if (**format_str == 'l')
		{
			parsed_fmt->flag |= F_L;
			(*format_str)++;
			if (**format_str && ft_strchr("hl", **format_str))
			{
				parsed_fmt->flag |= F_LL;
				(*format_str)++;
			}
		}
	}
}

void	read_int_in_format(char **format_str, char *chr_str, int *i)
{
	while (**format_str && ft_strchr(chr_str, **format_str))
	{
		if ('0' <= **format_str && **format_str <= '9' && *i != -1)
			*i = *i * 10 + (**format_str - '0');
		else if (**format_str == '.')
			*i = 0;
		else
			*i = -1;
		(*format_str)++;
	}
}

void	read_asterisk_in_format(t_parsed_fmt *parsed_fmt, va_list arg_list)
{
	if (parsed_fmt->field_width == -1)
	{
		parsed_fmt->field_width = va_arg(arg_list, int);
		parsed_fmt->flag |= (parsed_fmt->field_width < 0 ? F_MINUS : 0);
		parsed_fmt->field_width = ABS(parsed_fmt->field_width);
	}
	if (parsed_fmt->precision == -1)
	{
		parsed_fmt->precision = va_arg(arg_list, int);
		if (parsed_fmt->precision < 0)
			parsed_fmt->precision = INT_MAX;
	}
}

void	format_purser(char **format_str, t_parsed_fmt *parsed_fmt, va_list arg_list)
{
	parsed_fmt->conversion_spec = '\0';
	parsed_fmt->field_width = 0;
	parsed_fmt->flag = 0;
	parsed_fmt->precision = INT_MAX;
	read_flag(format_str, parsed_fmt);
	read_int_in_format(format_str, "0123456789*", &(parsed_fmt->field_width));
	read_int_in_format(format_str, "0123456789*.", &(parsed_fmt->precision));
	read_asterisk_in_format(parsed_fmt, arg_list);
	while (**format_str && ft_strchr("hlL", **format_str))
		(*format_str)++;
	parsed_fmt->conversion_spec = **format_str;
	if (**format_str)
		(*format_str)++;
}