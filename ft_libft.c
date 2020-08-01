/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 14:36:04 by tmurakam          #+#    #+#             */
/*   Updated: 2020/08/01 14:36:29 by tmurakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (dst != src)
	{
		while (i < n)
		{
			*((char *)dst + i) = *((char *)src + i);
			i++;
		}
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	char *i_p;

	i_p = (char *)s;
	while (*i_p != 0 && *i_p != c)
		i_p++;
	if (*i_p != c)
		i_p = 0;
	return (i_p);
}

int	ft_putstr(char *s, size_t len)
{
	return (write(1, s, len));
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*(s + i) != 0)
		i++;
	return (i);
}

int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*return_p;

	return_p = malloc(count * size);
	if (return_p)
		ft_bzero(return_p, count * size);
	return ((void *)return_p);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
		*((unsigned char*)b + i++) = (unsigned char)c;
	return (b);
}
