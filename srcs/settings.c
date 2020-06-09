/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:20:36 by user42            #+#    #+#             */
/*   Updated: 2020/06/09 12:41:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

int			check_cell(int *previous, int add, t_coord check, t_mlx_data *mlx)
{
	if (add == 1)
		check.x += 1;
	if (add == 2)
		check.x += -1;
	if (add == 3)
		check.y += 1;
	if (add == 4)
		check.y += -1;
	if (check.x >= mlx->cam->max_x || check.y >= mlx->cam->max_y || check.x < 0 || check.y < 0)
		return (1);
	if (previous[(int)check.x + (mlx->cam->max_x * (int)check.y)] == 0)
	{
		if (mlx->world_map[(int)check.y][(int)check.x] == -2)
			return (1);
		if (mlx->world_map[(int)check.y][(int)check.x] == 0 || mlx->world_map[(int)check.y][(int)check.x] == 2)
		{
			mlx->cam->x_intercept.x = check.x;
			mlx->cam->x_intercept.y = check.y;
			return (0);
		}
	}
	return (-1);
}

int			check_close(int **map, t_mlx_data *mlx, t_coord check, int *previous)
{
	previous[(int)check.x + (mlx->cam->max_x * (int)check.y)] = 1;
	if (check_cell(previous, 1, check, mlx) == 1)
		return (1);
	if (check_cell(previous, 1, check, mlx) == 0)
		if (check_close(map, mlx, mlx->cam->x_intercept, previous))
			return (1);
	if (check_cell(previous, 2, check, mlx) == 1)
		return (1);
	if (check_cell(previous, 2, check, mlx) == 0)
		if (check_close(map, mlx, mlx->cam->x_intercept, previous))
			return (1);
	if (check_cell(previous, 3, check, mlx) == 1)
		return (1);
	if (check_cell(previous, 3, check, mlx) == 0)
		if (check_close(map, mlx, mlx->cam->x_intercept, previous))
			return (1);
	if (check_cell(previous, 4, check, mlx) == 1)
		return (1);
	if (check_cell(previous, 4, check, mlx) == 0)
		if (check_close(map, mlx, mlx->cam->x_intercept, previous))
			return (1);
	return (0);
}

int			check_spawn_points(t_mlx_data *mlx)
{
	int flag;
	int i;
	int y;

	i = 0;
	flag = 0;
	while (mlx->world_map[i] != 0)
	{
		y = 0;
		while (mlx->world_map[i][y] != -1)
		{
			if (mlx->world_map[i][y] > 2)
			{
				if (flag != 0)
					return (print_error("More than one starting position on the map"));
				flag = 1;
			}
			y++;
		}
		i++;
	}
	return (0);
}

int			check_map(t_mlx_data *mlx)
{
	int		*previous;
	int		i;
	t_coord	start;

	if (check_spawn_points(mlx))
		return (1);
	if ((previous = malloc((mlx->cam->max_x * mlx->cam->max_y) * sizeof(int))) == 0)
		return (print_error("Malloc failed while checking map"));
	i = 0;
	while (i < mlx->cam->max_x * mlx->cam->max_y)
	{
		previous[i] = 0;
		i++;
	}
	start.x = mlx->cam->player_x;
	start.y = mlx->cam->player_y;
	if (check_close(mlx->world_map, mlx, start, previous))
	{
		free(previous);
		return (print_error("Map doesn't have closed walls"));
	}
	free(previous);
	return (0);
}

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
	if (set->north.img  == 0)
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
	if (parse_cub(set, mlx, argc, argv))
		return (1);
	if (verify_settings(set, mlx))
		return (1);
	set->wall_height = (float)set->s_width / (float)set->s_height / 3.0;
	mlx->win = mlx_new_window(mlx->mlx, set->s_width,
							set->s_height, "Cub3D");
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
			if (split_len(mlx->split) < 3)
				return (print_error("Resolution lacks a parameter."));
			set->s_width = ft_atoi(mlx->split[1]);
			set->s_height = ft_atoi(mlx->split[2]);
			if (set->s_width <= 1 || set->s_height <= 0)
				return (print_error("Resolution is too small."));
		}
		if (set_textures(set, line, mlx))
			return (1);
		if (set_colours(set, line, mlx))
			return (1);
	}
	split_free(mlx);
	return (0);
}
