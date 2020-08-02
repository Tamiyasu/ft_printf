/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 18:31:51 by tmurakam          #+#    #+#             */
/*   Updated: 2020/08/02 18:31:51 by tmurakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_HELPER_H
# define FT_PRINTF_HELPER_H

typedef struct		s_parsed_fmt
{	
	int				flag;
	int				field_width;
	int				prec;
	char			conversion_spec;
}					t_pfmt;

long long 			cast_i(long long i, t_pfmt *pfmt);
unsigned long long	cast_u(unsigned long long u, t_pfmt *pfmt);

# endif