/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_i.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:18:40 by tmurakam          #+#    #+#             */
/*   Updated: 2020/08/02 18:22:27 by tmurakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_c(t_pfmt *pfmt, int *c_cnt, va_list arg_list)
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
		*c_cnt += ft_putchar_fd(c, 1);
	i = 0;
	while (i++ < pfmt->field_width - 1)
		*c_cnt += ft_putchar_fd(fill_c, 1);
	if (!(pfmt->flag & F_MINUS))
		*c_cnt += ft_putchar_fd(c, 1);
}

void	write_s(t_pfmt *pfmt, int *c_cnt, va_list arg_list)
{
	int		i;
	char	fill_c;
	char	*str;

	str = va_arg(arg_list, char*);
	if (!str)
		str = "(null)";
	fill_c = ' ';
	if (pfmt->flag & F_ZERO && !(pfmt->flag & F_MINUS))
		fill_c = '0';
	if (pfmt->flag & F_MINUS)
		*c_cnt += ft_putstr(str, MIN(pfmt->prec, (int)ft_strlen(str)));
	i = 0;
	while (i++ < (int)pfmt->field_width - MIN(pfmt->prec, (int)ft_strlen(str)))
		*c_cnt += ft_putchar_fd(fill_c, 1);
	if (!(pfmt->flag & F_MINUS))
		*c_cnt += ft_putstr(str, MIN(pfmt->prec, (int)ft_strlen(str)));
}

void	write_d(t_pfmt *pfmt, int *c_cnt, va_list arg_list)
{
	long long	tmp;
	char		*str;
	int			base;
	char		*prefix;

	prefix = pfmt->flag & F_PLUS ? "+" : "";
	prefix = pfmt->flag & F_SPACE ? " " : "";
	base = 10;
	tmp = cast_i((int)va_arg(arg_list, long long), pfmt);
	if (pfmt->flag & F_ZERO && !(pfmt->flag & F_MINUS) && pfmt->prec == INT_MAX)
		pfmt->prec = pfmt->field_width - (tmp < 0 ? 1 : 0);
	if (!(str = ft_itoax(tmp, pfmt, base, prefix)))
		str = ft_strdup("(null)");
	if (pfmt->flag & F_MINUS)
		*c_cnt += ft_putstr(str, (int)ft_strlen(str));
	tmp = (int)pfmt->field_width - MAX(pfmt->prec, (int)ft_strlen(str));
	while (0 < tmp--)
		*c_cnt += ft_putchar_fd(' ', 1);
	if (!(pfmt->flag & F_MINUS))
		*c_cnt += ft_putstr(str, (int)ft_strlen(str));
	free(str);
}

char	*set_prefix(t_pfmt *pfmt)
{
	if (pfmt->flag & F_SHARP)
	{
		if (pfmt->conversion_spec == 'x')
			return (ft_strdup("0x"));
		if (pfmt->conversion_spec == 'X')
			return (ft_strdup("0x"));
		if (pfmt->conversion_spec == 'o')
			return (ft_strdup("0"));
		if (pfmt->conversion_spec == 'O')
			return (ft_strdup("0"));
	}
	return (ft_strdup(""));
}

int		set_base(t_pfmt *pfmt)
{
	if (pfmt->conversion_spec == 'x' || pfmt->conversion_spec == 'X')
		return (16);
	if (pfmt->conversion_spec == 'o' || pfmt->conversion_spec == 'O')
		return (8);
	return (10);
}

long long cast_i(long long i, t_pfmt *pfmt)
{
	if (pfmt->flag & F_HH)
		return ((char)i);
	if (pfmt->flag & F_LL)
		return ((long long)i);
	if (pfmt->flag & F_H)
		return ((short)i);
	if (pfmt->flag & F_L)
		return ((long)i);
	return ((int)i);
}

unsigned long long cast_u(unsigned long long u, t_pfmt *pfmt)
{
	if (pfmt->flag & F_HH)
		return ((unsigned char)u);
	if (pfmt->flag & F_LL)
		return ((unsigned long long)u);
	if (pfmt->flag & F_H)
		return ((unsigned short)u);
	if (pfmt->flag & F_L)
		return ((unsigned long)u);
	return ((unsigned int)u);
}

void	write_u(t_pfmt *pfmt, int *c_cnt, va_list arg_list)
{
	int					i;
	unsigned long long	u;
	char				*str;
	int					base;
	char				*prefix;

	prefix = set_prefix(pfmt);
	base = set_base(pfmt);
	u = cast_u(va_arg(arg_list, unsigned long long), pfmt);
	if (pfmt->flag & F_ZERO && pfmt->prec == INT_MAX)
		pfmt->prec = pfmt->field_width;
	if (!(str = ft_utoax(u, pfmt, base, prefix)))
		str = ft_strdup("(null)");
	if (pfmt->flag & F_MINUS)
		*c_cnt += ft_putstr(str, (int)ft_strlen(str));
	i = 0;
	while (i++ < (int)pfmt->field_width - MAX(pfmt->prec, (int)ft_strlen(str)))
		*c_cnt += ft_putchar_fd(' ', 1);
	if (!(pfmt->flag & F_MINUS))
		*c_cnt += ft_putstr(str, (int)ft_strlen(str));
	free(prefix);
	free(str);
}

void	write_p(t_pfmt *pfmt, int *c_cnt, va_list arg_list)
{
	int				i;
	unsigned long	u;
	char			fill_c;
	char			*str;
	int				base;

	base = 16;
	u = va_arg(arg_list, long);
	if (pfmt->flag & F_ZERO && pfmt->prec == INT_MAX)
		pfmt->prec = pfmt->field_width;
	str = ft_utoax(u, pfmt, base, "0x");
	if (!str)
		str = "(null)";
	fill_c = ' ';
	if (pfmt->flag & F_MINUS)
		*c_cnt += ft_putstr(str, (int)ft_strlen(str));
	i = 0;
	while (i++ < (int)pfmt->field_width - MAX(pfmt->prec, (int)ft_strlen(str)))
		*c_cnt += ft_putchar_fd(fill_c, 1);
	if (!(pfmt->flag & F_MINUS))
		*c_cnt += ft_putstr(str, (int)ft_strlen(str));
	free(str);
}
