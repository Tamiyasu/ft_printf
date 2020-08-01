/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 15:32:11 by tmurakam          #+#    #+#             */
/*   Updated: 2020/08/01 20:48:59 by tmurakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>

# define F_MINUS       0b1
# define F_PLUS       0b10
# define F_SPACE     0b100
# define F_ZERO     0b1000
# define F_SHARP   0b10000
# define F_L      0b100000
# define F_H     0b1000000
# define F_LL   0b10000000
# define F_HH  0b100000000

# define MIN(a, b) ((a) < (b) ? (a) : (b))
# define MAX(a, b) ((a) > (b) ? (a) : (b))
# define ABS(a) ((a) > 0 ? (a) : -1 * (a))

typedef struct	s_parsed_fmt
{
	int			flag;
	int			field_width;
	int			prec;
	char		conversion_spec;
}				t_pfmt;

void			read_flag(char **fmt_str, t_pfmt *pfmt);
void			read_int_in_format(char **fmt_str, char *chr_str, int *i);
void			read_asterisk_in_format(t_pfmt *pfmt, va_list arg_list);
void			read_hhll(char **fmt_str, t_pfmt *pfmt);
void			format_purser(char **fmt_str, t_pfmt *pfmt, va_list arg_list);

int				ft_printf(const char *fmt_str, ...);
int 			format_write(char **fmt_str, int *c_cnt, va_list arg_list);
char			*ft_itoax(long n, t_pfmt *pfmt, int base, char *pref);
char			*ft_utoax(unsigned long n, t_pfmt *pfmt, int base, char *pref);
void			read_asterisk_in_format(t_pfmt *pfmt, va_list arg_list);

void			*ft_calloc(size_t count, size_t size);
char			*ft_strchr(const char *s, int c);
int				ft_putstr(char *s, size_t len);
size_t			ft_strlen(const char *s);
int				ft_putchar_fd(char c, int fd);
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);

void			write_c(t_pfmt *pfmt, int *c_cnt, va_list arg_list);
void			write_s(t_pfmt *pfmt, int *c_cnt, va_list arg_list);
void			write_d(t_pfmt *pfmt, int *c_cnt, va_list arg_list);
void			write_u(t_pfmt *pfmt, int *c_cnt, va_list arg_list);
void			write_p(t_pfmt *pfmt, int *c_cnt, va_list arg_list);

#endif
