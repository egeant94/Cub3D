/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:20:36 by user42            #+#    #+#             */
/*   Updated: 2020/06/02 15:51:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

int		**create_map(void)
{
	int			**map;
	int			i;
	int			y;

	map = malloc(sizeof(int *) * 6);
	i = 0;
	while (i < 6)
	{
		map[i] = malloc(sizeof(int) * 6);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		y = 0;
		while (y < 6)
		{
			map[i][y] = 0;
			y++;
		}
		i++;
	}
	i = 0;
	while (i < 6)
	{
		map[0][i] = 1;
		map[5][i] = 1;
		map[i][0] = 1;
		map[i][5] = 1;
		i++;
	}
	map[1][2] = 1;
	map[2][3] = 2;
	map[2][2] = 2;
	map[3][2] = 1;
	i = 0;
	y = 0;
	while (i < 6)
	{
		y = 0;
		while (y < 6)
		{
			printf("%d, ", map[i][y]);
			y++;
		}
		printf("\n");
		i++;
	}
	return (map);
}

int			get_texture(t_texture *tex, char *path, t_mlx_data *mlx)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx, path, &tex->width, &tex->height);
	if (tex->img != 0)
	{
		tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
								&tex->line_length, &tex->endian);
		return (0);
	}
	else
		return (1);
}

int			print_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(1, "Error\n", 7);
	write(1, str, len);
	write(1, "\n", 1);
	return (1);
}

void		free_line(char **str)
{
	if (*str != 0)
	{
		free(*str);
		*str = 0;
	}
}

void		split_free(t_mlx_data *mlx)
{
	int	i;

	i = 0;
	if (mlx->split != 0)
	{
		while(mlx->split[i] != 0)
		{
			free(mlx->split[i]);
			i++;
		}
		free(mlx->split);
		mlx->split = 0;
	}
}

int			split_len(char **tab)
{
	int	i;

	i = 0;
	while(tab[i] != 0)
		i++;
	return (i);
}

int			line_to_set(t_settings *set, char *line, t_mlx_data *mlx)
{
	if ((mlx->split = ft_split(line, ' ')) == 0)
		return (print_error("Malloc failed while parsing .cub"));
	if (ft_strlen(line) > 0)
	{
		if (line[0] == 'R')
		{
			if (split_len(mlx->split) < 3)
				return (print_error("Resolution lacks a parameter."));
			set->s_width = ft_atoi(mlx->split[1]);
			set->s_height = ft_atoi(mlx->split[2]);
			if (set->s_width <= 1 || set->s_height <= 0)
				return (print_error("Resolution is too small."));
		}
	}
	split_free(mlx);
	return (0);
}

int			file_reading(t_settings *set, t_mlx_data *mlx)
{
	int ret;

	ret = get_next_line(mlx->cub_fd, &mlx->line);
	while (ret != 0)
	{
		if (ret == -1)
			return (print_error("Malloc failed while parsing .cub"));
		if (ft_isdigit(mlx->line[0]) || mlx->line[0] == ' ' || mlx->line[0] == '\t')
			break;
		if (line_to_set(set, mlx->line, mlx))
			return (1);
		ft_printf("%s\n", mlx->line);
		free_line(&mlx->line);
		ret = get_next_line(mlx->cub_fd, &mlx->line);
	}
	ft_printf("%d, %d\n", set->s_width, set->s_height);
	free_line(&mlx->line);
	(void)set;
	return (0);
}

int			parse_cub(t_settings *set, t_mlx_data *mlx, int argc, char **argv)
{
	if ((mlx->cub_fd = open(argv[1], O_RDONLY)) == -1)
		return (print_error(strerror(errno)));
	if (file_reading(set, mlx))
		return (1);
	if (argc > 2)
	{
		ft_printf("Saving first image\n");
		return (1);
	}
	return (0);
}

void		init_mlx(t_mlx_data *mlx)
{
	mlx->mlx = 0;
	mlx->win = 0;
	mlx->img = 0;
	mlx->bits_per_pixel = 0;
	mlx->line_length = 0;
	mlx->endian = 0;
	mlx->world_map = 0;
	mlx->cub_fd = 0;
	mlx->line = 0;
	mlx->split = 0;
}

int			init_settings(t_settings *set, t_mlx_data *mlx, int argc,
							char **argv)
{
	if (parse_cub(set, mlx, argc, argv))
		return (1);
	set->wall_height = (float)set->s_width / (float)set->s_height / 3.0;
	set->floor_c = 0xBBEFDECD;
	set->ceiling_c = 0x0000CCFF;
	mlx->world_map = create_map();
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, set->s_width,
							set->s_height, "Cub3D");
	if (get_texture(&set->north, "./textures/grass.xpm", mlx))
		return (print_error("North texture not found"));
	if (get_texture(&set->south, "./textures/brick.xpm", mlx))
		return (print_error("South texture not found"));
	if (get_texture(&set->east, "./textures/wood.xpm", mlx))
		return (print_error("East texture not found"));
	if (get_texture(&set->west, "./textures/metal.xpm", mlx))
		return (print_error("West texture not found"));
	if (get_texture(&set->sprite, "./textures/sprite.xpm", mlx))
		return (print_error("Sprite texture not found"));
	return (0);
}
