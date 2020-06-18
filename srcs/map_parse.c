/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 11:10:04 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 09:44:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			get_map(int ret, t_mlx_data *mlx)
{
	int		i;

	if ((mlx->world_map = malloc(2 * sizeof(*(mlx->world_map)))) == 0)
		return (print_error("Malloc failed while parsing map"));
	if ((mlx->world_map[0] = line_to_arr(mlx)) == 0)
		return (1);
	mlx->world_map[1] = 0;
	i = 1;
	while (ret != 0)
	{
		ret = get_next_line(mlx->cub_fd, &mlx->line);
		if (realloc_map(mlx, 1))
			return (1);
		if ((mlx->world_map[i] = line_to_arr(mlx)) == 0)
			return (1);
		i++;
	}
	if (format_map(mlx))
		return (1);
	return (0);
}

int			*line_to_arr(t_mlx_data *mlx)
{
	int		*arr;
	int		i;

	if ((arr = malloc((ft_strlen(mlx->line) + 1) * sizeof(*arr))) == 0)
	{
		print_error("Malloc failed while parsing the map");
		return (0);
	}
	arr[ft_strlen(mlx->line)] = -1;
	i = 0;
	while (mlx->line[i] != 0)
	{
		if (letter_to_number(mlx->line[i], arr, i))
		{
			print_error("Unknown character in the map");
			return (0);
		}
		i++;
	}
	free_line(&mlx->line);
	return (arr);
}

int			realloc_map(t_mlx_data *mlx, int size)
{
	int		i;
	int		**new_map;

	i = 0;
	while (mlx->world_map[i] != 0)
		i++;
	if ((new_map = malloc((i + size + 1) * sizeof(int *))) == 0)
		return (print_error("Malloc failed while parsing the map"));
	new_map[i + size] = 0;
	i = 0;
	while (mlx->world_map[i] != 0)
	{
		new_map[i] = mlx->world_map[i];
		i++;
	}
	free(mlx->world_map);
	mlx->world_map = new_map;
	return (0);
}

int			format_map(t_mlx_data *mlx)
{
	int	i;
	int y;

	i = 0;
	while (mlx->world_map[i] != 0)
	{
		y = 0;
		while (mlx->world_map[i][y] != -1)
			y++;
		if (y > mlx->cam->max_x)
			mlx->cam->max_x = y;
		i++;
	}
	mlx->cam->max_y = i;
	if (new_format(mlx, i, y))
		return (1);
	if (start_position(mlx, i, y))
		return (1);
	return (0);
}

int			new_format(t_mlx_data *mlx, int i, int y)
{
	int	*formated_line;

	i = 0;
	while (mlx->world_map[i] != 0)
	{
		if ((formated_line = malloc((mlx->cam->max_x + 1) * sizeof(int))) == 0)
			return (print_error("Malloc failed while parsing map"));
		formated_line[mlx->cam->max_x] = -1;
		y = 0;
		while (y < mlx->cam->max_x)
		{
			formated_line[y] = -2;
			y++;
		}
		y = 0;
		while (mlx->world_map[i][y] != -1)
		{
			formated_line[y] = mlx->world_map[i][y];
			y++;
		}
		free(mlx->world_map[i]);
		mlx->world_map[i] = formated_line;
		i++;
	}
	return (0);
}
