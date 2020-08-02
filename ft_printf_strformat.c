/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_strformat.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:56:54 by tmurakam          #+#    #+#             */
/*   Updated: 2020/08/02 20:13:30 by tmurakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	read_flag(char **format_str, t_pfmt *pfmt)
{
	while (**format_str && ft_strchr("-+ 0#", **format_str))
	{
		if (**format_str == '-')
			pfmt->flag |= F_MINUS;
		else if (**format_str == '+')
			pfmt->flag |= F_PLUS;
		else if (**format_str == ' ')
			pfmt->flag |= F_SPACE;
		else if (**format_str == '0')
			pfmt->flag |= F_ZERO;
		else if (**format_str == '#')
			pfmt->flag |= F_SHARP;
		(*format_str)++;
	}
}

void	read_hhll(char **format_str, t_pfmt *pfmt)
{
	if (**format_str && ft_strchr("hl", **format_str))
	{
		if (**format_str == 'h')
		{
			pfmt->flag |= F_H;
			(*format_str)++;
			if (**format_str && ft_strchr("hl", **format_str))
			{
				pfmt->flag |= F_HH;
				(*format_str)++;
			}
		}
		else if (**format_str == 'l')
		{
			pfmt->flag |= F_L;
			(*format_str)++;
			if (**format_str && ft_strchr("hl", **format_str))
			{
				pfmt->flag |= F_LL;
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

void	read_asterisk_in_format(t_pfmt *pfmt, va_list arg_list)
{
	if (pfmt->field_width == -1)
	{
		pfmt->field_width = va_arg(arg_list, int);
		pfmt->flag |= (pfmt->field_width < 0 ? F_MINUS : 0);
		pfmt->field_width = ABS(pfmt->field_width);
	}
	if (pfmt->prec == -1)
	{
		pfmt->prec = va_arg(arg_list, int);
		if (pfmt->prec < 0)
			pfmt->prec = INT_MAX;
	}
}

void	format_purser(char **format_str, t_pfmt *pfmt, va_list arg_list)
{
	pfmt->conversion_spec = '\0';
	pfmt->field_width = 0;
	pfmt->flag = 0;
	pfmt->prec = INT_MAX;
	read_flag(format_str, pfmt);
	read_int_in_format(format_str, "0123456789*", &(pfmt->field_width));
	read_int_in_format(format_str, "0123456789*.", &(pfmt->prec));
	read_hhll(format_str, pfmt);
	read_asterisk_in_format(pfmt, arg_list);
	pfmt->conversion_spec = **format_str;
	if (**format_str)
		(*format_str)++;
}
