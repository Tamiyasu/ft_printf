/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 18:42:19 by tmurakam          #+#    #+#             */
/*   Updated: 2020/08/02 18:46:42 by tmurakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*set_prefix(t_pfmt *pfmt)
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

int					set_base(t_pfmt *pfmt)
{
	if (pfmt->conversion_spec == 'x' || pfmt->conversion_spec == 'X')
		return (16);
	if (pfmt->conversion_spec == 'o' || pfmt->conversion_spec == 'O')
		return (8);
	return (10);
}

long long			cast_i(long long i, t_pfmt *pfmt)
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

unsigned long long	cast_u(unsigned long long u, t_pfmt *pfmt)
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