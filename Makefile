# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osboxes <osboxes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/12 15:21:23 by egeant            #+#    #+#              #
#    Updated: 2020/01/27 12:54:04 by osboxes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SDIR	= srcs/
ODIR	= obj/
HEADERS	= includes
SOURCES	= helloworld.c
SRCS	= $(addprefix $(SDIR),$(SOURCES))
OBJS	= $(addprefix $(ODIR),$(SOURCES:.c=.o))
LIBFT	= ./libft/libft.a
MLXFLAGS= -L/home/osboxes/42/Cub3D/minilibx -lm -lmlx_Linux -lbsd -lXext -lX11
CFLAGS	= -Wall -Wextra -Werror
CC		= gcc
NAME	= Cub3d
RM		= rm -f

all:	$(NAME)

$(NAME):	$(OBJS)
			@make -C libft
			@gcc $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIBFT) -o $(NAME)
			
$(ODIR)%.o: $(SDIR)%.c
		@mkdir -p $(ODIR)
		@$(CC) $(MLXFLAGS) $(CFLAGS) -c $< -I $(HEADERS) -o $@

clean:
		@$(RM) $(OBJS)
		@rm -rf $(ODIR)
		@make clean -C libft

fclean: clean
		@$(RM) $(NAME)
		@make fclean -C libft

re:	fclean all

.PHONY : $(NAME) all clean fclean re
