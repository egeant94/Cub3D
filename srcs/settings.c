/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:20:36 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 13:14:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			verify_settings(t_settings *set, t_mlx_data *mlx)
{
	int	x;
	int y;

	mlx_get_screen_size(mlx->mlx, &x, &y);
	if (set->s_width > x)
		set->s_width = x;
	if (set->s_height > y)
		set->s_height = y;
	if (set->floor_c == -1)
		return (print_error("Floor color is missing."));
	if (set->ceiling_c == -1)
		return (print_error("Ceiling color is missing."));
	if (set->north.img == 0)
		return (print_error("North texture is missing."));
	if (set->south.img == 0)
		return (print_error("South texture is missing."));
	if (set->west.img == 0)
		return (print_error("West texture is missing."));
	if (set->east.img == 0)
		return (print_error("East texture is missing."));
	if (set->sprite.img == 0)
		return (print_error("Sprite texture is missing."));
	if (check_map(mlx))
		return (1);
	return (0);
}

int			init_settings(t_settings *set, t_mlx_data *mlx, int argc,
							char **argv)
{
	init_set(set);
	if (parse_cub(set, mlx, argv))
		return (1);
	if (verify_settings(set, mlx))
		return (1);
	if (set->s_width == -1 || set->s_height == -1)
		return (print_error("Resolution is missing"));
	set->wall_height = (float)set->s_width / (float)set->s_height / 3.0;
	mlx->cam_speed = 9 * ((set->s_width * set->s_height) / (1280.0 * 720.0))
					* SPEED;
	if (mlx->cam_speed <= 0)
		mlx->cam_speed = 1;
	mlx->cam->movement_speed = 9 * ((1280.0 * 720.0) /
								(set->s_width * set->s_height));
	if (argc > 2)
		if (save_bmp(mlx))
			return (1);
	mlx->win = mlx_new_window(mlx->mlx, set->s_width,
							set->s_height, "Cub3D");
	return (0);
}

int			parse_cub(t_settings *set, t_mlx_data *mlx, char **argv)
{
	if ((mlx->cub_fd = open(argv[1], O_RDONLY)) == -1)
		return (print_error(strerror(errno)));
	if (file_reading(set, mlx))
		return (1);
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
		if (ft_isdigit(mlx->line[0]) || mlx->line[0] == ' '
			|| mlx->line[0] == '\t')
			break ;
		if (line_to_set(set, mlx->line, mlx))
			return (1);
		free_line(&mlx->line);
		ret = get_next_line(mlx->cub_fd, &mlx->line);
	}
	if (ret != 0)
	{
		if (get_map(ret, mlx))
			return (1);
	}
	return (0);
}

int			line_to_set(t_settings *set, char *line, t_mlx_data *mlx)
{
	if ((mlx->split = ft_split(line, ' ')) == 0)
		return (print_error("Malloc failed while parsing .cub"));
	if (ft_strlen(line) > 0)
	{
		if (line[0] == 'R')
		{
			if (set->s_width != -1 || set->s_height != -1)
				return (print_error("Resolution is defined multiple times"));
			if (split_len(mlx->split) < 3)
				return (print_error("Resolution lacks a parameter"));
			if (check_line(line))
				return (print_error("Resolution is flawed"));
			set->s_width = ft_atoi(mlx->split[1]);
			set->s_height = ft_atoi(mlx->split[2]);
			if (set->s_width <= 2 || set->s_height <= 2)
				return (print_error("Resolution is too small"));
		}
		if (set_textures(set, line, mlx))
			return (1);
		if (set_colours(set, line, mlx))
			return (1);
	}
	split_free(mlx);
	return (0);
}
