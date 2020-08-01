/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_i.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:18:40 by tmurakam          #+#    #+#             */
/*   Updated: 2020/08/01 17:28:02 by tmurakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_c(t_pfmt *pfmt, int *char_count, va_list arg_list)
{
	int		i;
	char	c;
	char	fill_c;

	fill_c = ' ';
	if (pfmt->conversion_spec == '%')
		c = '%';
	else
		c = va_arg(arg_list, int);
	if (pfmt->flag & F_ZERO && !(pfmt->flag & F_MINUS))
		fill_c = '0';
	if (pfmt->flag & F_MINUS)
		*char_count += ft_putchar_fd(c, 1);
	i = 0;
	while (i++ < pfmt->field_width - 1)
		*char_count += ft_putchar_fd(fill_c, 1);
	if (!(pfmt->flag & F_MINUS))
		*char_count += ft_putchar_fd(c, 1);
}

void	write_s(t_pfmt *pfmt, int *char_count, va_list arg_list)
{
	int i;
	char fill_c;
	char *str;

	str = va_arg(arg_list, char*);
	if(!str)
		str = "(null)";
	fill_c = ' ';
	if (pfmt->flag & F_ZERO && !(pfmt->flag & F_MINUS))
		fill_c = '0';
	if (pfmt->flag & F_MINUS)
		*char_count += ft_putstr(str, MIN(pfmt->precision, (int)ft_strlen(str)));
	i = 0;
	while (i++ < (int)pfmt->field_width - MIN(pfmt->precision, (int)ft_strlen(str)))
		*char_count += ft_putchar_fd(fill_c, 1);
	if (!(pfmt->flag & F_MINUS))
		*char_count += ft_putstr(str, MIN(pfmt->precision, (int)ft_strlen(str)));
}

void	write_d(t_pfmt *pfmt, int *char_count, va_list arg_list)
{
	int		i;
	int		d;
	char	fill_c;
	char	*str;
	int		base;
	char	*prefix;
	
	prefix = "";
	if (pfmt->flag & F_PLUS)
		prefix = "+";
	if (pfmt->flag & F_SPACE)
		prefix = " ";
	base = 10;
	d = va_arg(arg_list, int);
	if (pfmt->flag & F_ZERO  && !(pfmt->flag & F_MINUS) && pfmt->precision == INT_MAX)
		pfmt->precision = pfmt->field_width - (d < 0 ? 1 : 0);
	str = ft_itoax(d, pfmt, base, prefix);
	if(!str)
		str = "(null)";
	fill_c = ' ';
	if (pfmt->flag & F_MINUS)
	{
		i = 0;
		*char_count += ft_putstr(str, (int)ft_strlen(str));
	}
	i = 0;
	while (i++ < (int)pfmt->field_width - MAX(pfmt->precision, (int)ft_strlen(str)))
		*char_count += ft_putchar_fd(fill_c, 1);
	if (!(pfmt->flag & F_MINUS))
	{
		i = 0;
		*char_count += ft_putstr(str, (int)ft_strlen(str));
	}
	free(str);
}

void	write_u(t_pfmt *pfmt, int *char_count, va_list arg_list)
{
	int				i;
	unsigned int	u;
	char			fill_c;
	char			*str;
	int				base;

	base = 10;
	if (pfmt->conversion_spec == 'x' || pfmt->conversion_spec == 'X')
		base = 16;
	if (pfmt->conversion_spec == 'o')
		base = 8;
	u = va_arg(arg_list, unsigned int);
	if (pfmt->flag & F_ZERO && pfmt->precision == INT_MAX)
		pfmt->precision = pfmt->field_width;
	else if (pfmt->flag & F_ZERO && !(pfmt->flag & F_MINUS) && pfmt->precision == INT_MAX)
		fill_c = '0';
	str = ft_utoax(u, pfmt, base, "");
	if(!str)
		str = "(null)";
	fill_c = ' ';
	if (pfmt->flag & F_MINUS)
	{
		i = 0;
		*char_count += ft_putstr(str, (int)ft_strlen(str));
	}
	i = 0;
	while (i++ < (int)pfmt->field_width - MAX(pfmt->precision, (int)ft_strlen(str)))
		*char_count += ft_putchar_fd(fill_c, 1);
	if (!(pfmt->flag & F_MINUS))
	{
		i = 0;
		*char_count += ft_putstr(str, (int)ft_strlen(str));
	}
	free(str);
}

void	write_p(t_pfmt *pfmt, int *char_count, va_list arg_list)
{
	int				i;
	unsigned long	u;
	char			fill_c;
	char			*str;
	int				base;

	base = 16;
	u = va_arg(arg_list, long);
	if (pfmt->flag & F_ZERO && pfmt->precision == INT_MAX)
		pfmt->precision = pfmt->field_width;
	else if (pfmt->flag & F_ZERO && !(pfmt->flag & F_MINUS) && pfmt->precision == INT_MAX)
		fill_c = '0';
	str = ft_utoax(u, pfmt, base, "0x");
	if(!str)
		str = "(null)";
	fill_c = ' ';
	if (pfmt->flag & F_MINUS)
	{
		i = 0;
		while (i++ < pfmt->precision - (int)ft_strlen(str))
			*char_count += ft_putchar_fd('0', 1);
		*char_count += ft_putstr(str, (int)ft_strlen(str));
	}
	i = 0;
	while (i++ < (int)pfmt->field_width - MAX(pfmt->precision, (int)ft_strlen(str)))
		*char_count += ft_putchar_fd(fill_c, 1);
	if (!(pfmt->flag & F_MINUS))
	{
		i = 0;
		while (i++ < pfmt->precision - (int)ft_strlen(str))
			*char_count += ft_putchar_fd('0', 1);
		*char_count += ft_putstr(str, (int)ft_strlen(str));
	}
	free(str);
}
