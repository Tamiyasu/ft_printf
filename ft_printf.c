/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:42:55 by tmurakam          #+#    #+#             */
/*   Updated: 2020/07/21 22:18:07 by tmurakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

int	ft_printf(const char *format_str, ...)
{
	va_list	arg_list;
	int 	char_count;

	char_count = 0;
	while(*format_str)
	{
		if(*format_str != '%')
			char_count += write(1, format_str++, 1);
		else
			char_count += format_write(&format_str, );
    }

	return (char_count);
}

#include <stdio.h>


int main()
{
	int ret_i;
	ret_i = ft_printf("test\n");

	printf("ret_i : %d", ret_i);
    return (0);
}