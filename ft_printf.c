/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:42:55 by tmurakam          #+#    #+#             */
/*   Updated: 2020/08/01 17:28:48 by tmurakam         ###   ########.fr       */
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

int format_write(char **format_str, int *char_count, va_list arg_list)
{
	t_pfmt	pfmt;
	int		char_count_in_format;

	char_count_in_format = 0;
	char_count_in_format++;
	(*format_str)++;
	format_purser(format_str, &pfmt, arg_list);
	if (pfmt.conversion_spec == 's')
		write_s(&pfmt, char_count, arg_list);
	else if (pfmt.conversion_spec == 'd' || pfmt.conversion_spec == 'i')
		write_d(&pfmt, char_count, arg_list);
	else if (pfmt.conversion_spec == 'u' ||
			pfmt.conversion_spec == 'x' || pfmt.conversion_spec == 'X' ||
			pfmt.conversion_spec == 'o')
		write_u(&pfmt, char_count, arg_list);
	else if (pfmt.conversion_spec == 'c' || pfmt.conversion_spec == '%')
		write_c(&pfmt, char_count, arg_list);
	else if (pfmt.conversion_spec == 'p')
		write_p(&pfmt, char_count, arg_list);
	return (1);	
}

char	*ft_utoax(unsigned long n, t_pfmt *pfmt, int base, char *prefix)
{
	char			*return_s;
	int				order;
	int				i;
	unsigned long	n_copy;
	char			base_origin_10;

	base_origin_10 = 'a';
	if (pfmt->conversion_spec == 'X')
		base_origin_10 = 'A';
	if (n == 0 && pfmt->precision == 0)
	{
		if (!(return_s = ft_calloc(1 + ft_strlen(prefix), 1)))
			return(return_s);
		ft_memcpy(return_s, prefix, ft_strlen(prefix));		
		return (return_s);
	}
	if (pfmt->precision == INT_MAX)
		pfmt->precision = 0;
	n_copy = n;
	order = 1;
	while (n_copy /= base)
		order++;
	order = MAX(order, pfmt->precision) + ft_strlen(prefix);
	if(!(return_s = ft_calloc(order + 1, sizeof(char))))
		return (return_s);
	ft_memset(return_s, '0', order);
	*(return_s + order) = '\0';
	ft_memcpy(return_s, prefix, ft_strlen(prefix));
	i = 0;
	while (n)
	{
		*(return_s + order - ++i) = ABS(n % base) + (ABS(n % base) < 10 ? '0' : base_origin_10 - 10);
		n /= base;
	}
	return (return_s);
}

char	*ft_itoax(int n, t_pfmt *pfmt, int base, char *prefix)
{
	char	*return_s;
	int		order;
	int		i;
	int		n_copy;

	if(n < 0)
		prefix = "-";
	if (n == 0 && pfmt->precision == 0)
	{
		if (!(return_s = ft_calloc(1 + ft_strlen(prefix), 1)))
			return(return_s);
		ft_memcpy(return_s, prefix, ft_strlen(prefix));		
		return (return_s);
	}
	if (pfmt->precision == INT_MAX)
		pfmt->precision = 0;
	n_copy = n;
	order = 1;
	while (n_copy /= base)
		order++;
	order = MAX(order, pfmt->precision) + ft_strlen(prefix);

	if(!(return_s = ft_calloc(order + 1, sizeof(char))))
		return (return_s);
	ft_memset(return_s, '0', order);
	*(return_s + order) = '\0';
	ft_memcpy(return_s, prefix, ft_strlen(prefix));
	i = 0;
	while (n)
	{
		*(return_s + order - ++i) = ABS(n % base) + (ABS(n % base) < 10 ? '0' : 'a' - 10);
		n /= base;
	}
	return (return_s);
}
