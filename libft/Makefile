# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/12 15:21:23 by egeant            #+#    #+#              #
#    Updated: 2020/06/02 11:07:11 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c	\
			ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c ft_strjoin.c	\
			ft_substr.c ft_strdup.c ft_calloc.c ft_atoi.c ft_strnstr.c	\
			ft_strlcat.c ft_strlcpy.c ft_strncmp.c ft_strrchr.c			\
			ft_strchr.c ft_tolower.c ft_toupper.c ft_isprint.c 			\
			ft_isascii.c ft_isalnum.c ft_isdigit.c ft_isalpha.c			\
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c	\
			ft_memmove.c ft_memchr.c ft_memcmp.c get_next_line_utils.c	\
			get_next_line.c
CFLAGS	= -Wall -Wextra -Werror
CC		= gcc
OBJS	= ${SRCS:.c=.o}
NAME	= libft.a
RM		= rm -f
HEADERS	= .

all:	${NAME}

$(NAME):	${OBJS} 
			ar rc ${NAME} ${OBJS}
			
.c.o:
		${CC} ${CFLAGS} -I ${HEADERS} -c $< -o ${<:.c=.o}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:	fclean all

.PHONY : ${NAME} all clean fclean re
