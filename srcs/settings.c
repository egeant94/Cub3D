/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:20:36 by user42            #+#    #+#             */
/*   Updated: 2020/06/01 12:30:24 by user42           ###   ########.fr       */
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
		return (1);
	}
	else
		return (-1);
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

int			parse_cub(t_settings *set, t_mlx_data *mlx, int argc, char **argv)
{
	int	fd;

	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (print_error("Config file doesn't exist"));
	(void)set;
	(void)mlx;
	(void)argc;
	return (0);
}

int			init_settings(t_settings *set, t_mlx_data *mlx, int argc,
							char **argv)
{
	if (parse_cub(set, mlx, argc, argv))
		return (1);
	set->s_width = 1280;
	set->s_height = 720;
	set->wall_height = (float)set->s_width / (float)set->s_height / 3.0;
	set->floor_c = 0xBBEFDECD;
	set->ceiling_c = 0x0000CCFF;
	get_texture(&set->north, "./textures/grass.xpm", mlx);
	get_texture(&set->south, "./textures/brick.xpm", mlx);
	get_texture(&set->west, "./textures/metal.xpm", mlx);
	get_texture(&set->east, "./textures/wood.xpm", mlx);
	get_texture(&set->sprite, "./textures/sprite.xpm", mlx);
	mlx->world_map = create_map();
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, set->s_width,
							set->s_height, "Cub3D");
	return (0);
}
