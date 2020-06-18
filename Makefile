# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/12 15:21:23 by egeant            #+#    #+#              #
#    Updated: 2020/06/11 09:59:26 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SDIR	= srcs/
ODIR	= obj/
HEADERS	= includes
SOURCES	= 	angles.c display.c display_utils.c main.c movements.c ray_caster.c	\
			settings.c key_hooks.c colors.c map_parse.c start_pos.c				\
			free_utils.c rgb_parse.c settings_utils.c calc_sprites.c			\
			display_sprites.c ray_caster_utils.c check_map.c save_bmp.c
SRCS	= $(addprefix $(SDIR),$(SOURCES))
OBJS	= $(addprefix $(ODIR),$(SOURCES:.c=.o))
LIBFT	= ./libft/libft.a
MLXFLAGS= -L./minilibx_linux -lm -lmlx_Linux -lbsd -lXext -lX11
CFLAGS	= -Wall -Wextra -Werror
CC		= gcc
NAME	= cub
EXT		= 3D
RM		= rm -f

all:	$(NAME)$(EXT)

$(NAME)$(EXT)	:	$(OBJS)
					make -C minilibx_linux
					make -C libft
					gcc $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIBFT) -o $(NAME)$(EXT)
			
$(ODIR)%.o: $(SDIR)%.c
		@mkdir -p $(ODIR)
		$(CC) $(MLXFLAGS) $(CFLAGS) -c $< -I $(HEADERS) -o $@

clean:
		$(RM) $(OBJS)
		rm -rf $(ODIR)
		make clean -C libft

fclean: clean
		$(RM) $(NAME)$(EXT)
		make fclean -C libft
		make clean -C minilibx_linux

re:	fclean all

.PHONY : $(NAME) all clean fclean re
