/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 15:32:11 by tmurakam          #+#    #+#             */
/*   Updated: 2020/07/26 15:32:11 by tmurakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#include <stdio.h>

# include <unistd.h>
# include <stdarg.h>

# define F_MINUS 0b1
# define F_PLUS 0b10
# define F_SPACE 0b100
# define F_ZERO 0b1000
# define F_SHARP 0b10000

# define MIN(a, b) ((a) < (b) ? (a) : (b))
# define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct  s_parsed_fmt
{
    int flag;
    int field_width;
    int precision;
    char conversion_spec; //diouxXfFeEgGaAcsb
}               t_parsed_fmt;

int	ft_printf(const char *format_str, ...);
int format_write(char **format_str, int *char_count, va_list arg_list);

char	*ft_strchr(const char *s, int c);
int	ft_putstr(char *s, size_t len);
size_t	ft_strlen(const char *s);
int	ft_putchar_fd(char c, int fd);
int	ft_putnbr_fd(int n, int fd);

void write_c(t_parsed_fmt *parsed_fmt, int *char_count, va_list arg_list);


#endif
