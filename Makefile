# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmurakam <tmurakam@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/27 22:10:42 by tmurakam          #+#    #+#              #
#    Updated: 2020/07/27 22:10:42 by tmurakam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
RM = rm -f
SRCS = ./ft_printf.c
SRCS += ./ft_printf_strformat.c
SRCS += ./ft_printf_write_i.c
SRCS += ./ft_printf_helper.c
SRCS += ./ft_libft_mem.c
SRCS += ./ft_libft_str.c
OBJS = ${SRCS:.c=.o}
all: ${NAME}
bonus: ${OBJS} ${BONUS_OBJS}
	ar rc ${NAME} $^
${NAME}: ${OBJS}
	ar rc ${NAME} $^
.c.o:
	gcc -Wall -Wextra -Werror -c $< -o $@
clean:
	${RM} ${OBJS} ${BONUS_OBJS}
fclean: clean
	${RM} ${NAME}
re:	fclean all
.PHONY: all clean fclean re