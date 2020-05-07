# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/12 15:21:23 by egeant            #+#    #+#              #
#    Updated: 2020/05/07 17:18:10 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SDIR	= srcs/
# SDIR	= tests/
ODIR	= obj/
HEADERS	= includes
SOURCES	= angles.c display.c display_utils.c main.c movements.c ray_caster.c settings.c key_hooks.c
# SOURCES	= test.c
SRCS	= $(addprefix $(SDIR),$(SOURCES))
OBJS	= $(addprefix $(ODIR),$(SOURCES:.c=.o))
LIBFT	= ./libft/libft.a
MLXFLAGS= -L./minilibx_linux -lm -lmlx_Linux -lbsd -lXext -lX11 -L./printf -lftprintf
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address
CC		= gcc
NAME	= Cub3d
RM		= rm -f

all:	$(NAME)

$(NAME):	$(OBJS)
			@make -C libft
			@make -C minilibx_linux
			@make -C printf
			@gcc $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIBFT) -o $(NAME)
			
$(ODIR)%.o: $(SDIR)%.c
		@mkdir -p $(ODIR)
		@$(CC) $(MLXFLAGS) $(CFLAGS) -c $< -I $(HEADERS) -o $@

clean:
		@$(RM) $(OBJS)
		@rm -rf $(ODIR)
		@make clean -C libft
		@make clean -C printf

fclean: clean
		@$(RM) $(NAME)
		@make fclean -C libft
		@make clean -C minilibx_linux
		@make fclean -C printf

re:	fclean all

.PHONY : $(NAME) all clean fclean re
