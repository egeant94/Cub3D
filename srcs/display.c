/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:51:03 by user42            #+#    #+#             */
/*   Updated: 2020/04/27 22:53:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

void	my_mlx_pixel_put(t_mlx_data *mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	print_vertical_line(t_mlx_data *mlx, int x, float dist, t_camera cam)
{
	float		y;
	float		wall;
	int			color;

	if (cam.h_o_v == 1 && cam.tile_step_x == 1)
		color = 0x00FF0000;
	if (cam.h_o_v == 1 && cam.tile_step_x == -1)
		color = 0x0000FF00;
	if (cam.h_o_v == 2 && cam.tile_step_y == -1)
		color = 0x000000FF;
	if (cam.h_o_v == 2 && cam.tile_step_y == 1)
		color = 0x00FFF44F;
	y = 0;
	wall = (float)WALL_HEIGHT / dist;
	while (y < SCREEN_HEIGHT / 2)
	{
		if ((y / (SCREEN_HEIGHT / 2)) < wall)
		{
			my_mlx_pixel_put(mlx, x, SCREEN_HEIGHT / 2 + y, color);
			my_mlx_pixel_put(mlx, x, SCREEN_HEIGHT / 2 - y, color);
		}
		y++;
	}
}

void	floor_and_ceiling(t_mlx_data *mlx)
{
	int		x;
	int		y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			if (y < SCREEN_HEIGHT / 2)
				my_mlx_pixel_put(mlx, x, y, CEILING);
			else
				my_mlx_pixel_put(mlx, x, y, FLOOR);
			y++;
		}
		x++;
	}
}

void	init_camera(t_camera *cam)
{
	cam->player_x = 4;
	cam->player_y = 2;
	cam->player_dx = 0.616199;
	cam->player_dy = 0.600000;
	cam->h_o_v = 0;
	cam->beta_ang = 174;
	cam->theta_ang = 0;
	cam->x_intercept.x = 0;
	cam->x_intercept.y = 0;
	cam->y_intercept.x = 0;
	cam->y_intercept.y = 0;
	cam->x_step = 0;
	cam->y_step = 0;
	cam->tile_step_x = 0;
	cam->tile_step_y = 0;
}
