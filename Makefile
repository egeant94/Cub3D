# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/12 15:21:23 by egeant            #+#    #+#              #
#    Updated: 2020/04/27 22:52:47 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SDIR	= srcs/
ODIR	= obj/
HEADERS	= includes
SOURCES	= main.c ray_caster.c angles.c display.c movements.c
SRCS	= $(addprefix $(SDIR),$(SOURCES))
OBJS	= $(addprefix $(ODIR),$(SOURCES:.c=.o))
LIBFT	= ./libft/libft.a
MLXFLAGS= -L./minilibx_linux -lm -lmlx_Linux -lbsd -lXext -lX11
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address
CC		= gcc
NAME	= Cub3d
RM		= rm -f

all:	$(NAME)

$(NAME):	$(OBJS)
			@make -C libft
			@make -C minilibx_linux
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
		@make clean -C minilibx_linux

re:	fclean all

.PHONY : $(NAME) all clean fclean re
