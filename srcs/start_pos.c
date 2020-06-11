/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 11:15:59 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 09:44:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int			start_position(t_mlx_data *mlx, int i, int y)
{
	i = 0;
	while (mlx->world_map[i] != 0)
	{
		y = 0;
		while (mlx->world_map[i][y] != -1)
		{
			if (mlx->world_map[i][y] == 3)
				number_to_pos(mlx->cam, i, y, 3);
			if (mlx->world_map[i][y] == 4)
				number_to_pos(mlx->cam, i, y, 4);
			if (mlx->world_map[i][y] == 5)
				number_to_pos(mlx->cam, i, y, 5);
			if (mlx->world_map[i][y] == 6)
				number_to_pos(mlx->cam, i, y, 6);
			y++;
		}
		i++;
	}
	if (mlx->cam->player_x == -1)
		return (print_error("No start position in map (N, S, W or E)"));
	return (0);
}

void		number_to_pos(t_camera *cam, int i, int y, int nb)
{
	cam->player_x = y;
	cam->player_y = i;
	if (nb == 3)
		cam->beta_ang = 90;
	if (nb == 4)
		cam->beta_ang = 270;
	if (nb == 5)
		cam->beta_ang = 180;
	if (nb == 6)
		cam->beta_ang = 0;
}

int			letter_to_number(char c, int *arr, int i)
{
	if (c == ' ')
		arr[i] = -2;
	else if (c == '0')
		arr[i] = 0;
	else if (c == '1')
		arr[i] = 1;
	else if (c == '2')
		arr[i] = 2;
	else if (c == 'N')
		arr[i] = 3;
	else if (c == 'S')
		arr[i] = 4;
	else if (c == 'W')
		arr[i] = 5;
	else if (c == 'E')
		arr[i] = 6;
	else
	{
		free(arr);
		return (-1);
	}
	return (0);
}
