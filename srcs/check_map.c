/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 14:01:59 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 09:43:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	if (check.x >= mlx->cam->max_x || check.y >= mlx->cam->max_y ||
		check.x < 0 || check.y < 0)
		return (1);
	if (previous[(int)check.x + (mlx->cam->max_x * (int)check.y)] == 0)
	{
		if (mlx->world_map[(int)check.y][(int)check.x] == -2)
			return (1);
		if (mlx->world_map[(int)check.y][(int)check.x] == 0 ||
			mlx->world_map[(int)check.y][(int)check.x] == 2)
		{
			mlx->cam->x_intercept.x = check.x;
			mlx->cam->x_intercept.y = check.y;
			return (0);
		}
	}
	return (-1);
}

int			check_close(int **map, t_mlx_data *mlx, t_coord check, int *prev)
{
	prev[(int)check.x + (mlx->cam->max_x * (int)check.y)] = 1;
	if (check_cell(prev, 1, check, mlx) == 1)
		return (1);
	if (check_cell(prev, 1, check, mlx) == 0)
		if (check_close(map, mlx, mlx->cam->x_intercept, prev))
			return (1);
	if (check_cell(prev, 2, check, mlx) == 1)
		return (1);
	if (check_cell(prev, 2, check, mlx) == 0)
		if (check_close(map, mlx, mlx->cam->x_intercept, prev))
			return (1);
	if (check_cell(prev, 3, check, mlx) == 1)
		return (1);
	if (check_cell(prev, 3, check, mlx) == 0)
		if (check_close(map, mlx, mlx->cam->x_intercept, prev))
			return (1);
	if (check_cell(prev, 4, check, mlx) == 1)
		return (1);
	if (check_cell(prev, 4, check, mlx) == 0)
		if (check_close(map, mlx, mlx->cam->x_intercept, prev))
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
					return (print_error("More than one starting position"));
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
	if ((previous = malloc((mlx->cam->max_x * mlx->cam->max_y)
							* sizeof(int))) == 0)
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
