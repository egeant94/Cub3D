/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:51:03 by user42            #+#    #+#             */
/*   Updated: 2020/05/05 14:05:25 by user42           ###   ########.fr       */
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
	float		wall_offset;
	float		tex_y;
	t_texture	*tex;

	if (cam.h_o_v == 2 && cam.tile_step_x == 1)
		tex = &mlx->set->east;
	if (cam.h_o_v == 2 && cam.tile_step_x == -1)
		tex = &mlx->set->west;
	if (cam.h_o_v == 1 && cam.tile_step_y == -1)
		tex = &mlx->set->south;
	if (cam.h_o_v == 1 && cam.tile_step_y == 1)
		tex = &mlx->set->north;
	wall = (float)WALL_HEIGHT / dist;
	wall_offset = ((1 - wall) / 2) * mlx->set->s_height;
	y = wall_offset;
	if (wall_offset < 0)	
		y = 0;
	tex_y = 0;
	if (wall_offset < 0)
		tex_y = (wall - 1) / 2 * tex->height;
	while (y < (mlx->set->s_height - wall_offset) && y < mlx->set->s_height)
	{	
		if (wall_offset > 0)
			tex_y += tex->height / (mlx->set->s_height - wall_offset * 2);
		else
			tex_y += (tex->height - ((wall - 1) * tex->height)) / mlx->set->s_height;
		if (mlx->cam->h_o_v == 1)
		{
			my_mlx_pixel_put(mlx, x, y, my_mlx_pixel_reverse(tex, (mlx->cam->y_intercept.x -(int)mlx->cam->y_intercept.x) * tex->width, (int)tex_y));
		}
		if (mlx->cam->h_o_v == 2)
			my_mlx_pixel_put(mlx, x, y, my_mlx_pixel_reverse(tex,(mlx->cam->x_intercept.y -(int)mlx->cam->x_intercept.y) * tex->width, (int)tex_y));

		y++;
	}
}

int		my_mlx_pixel_reverse(t_texture *mlx, int x, int y)
{
	char *color;

	color = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	return (*(int *)color);
}

void	floor_and_ceiling(t_mlx_data *mlx)
{
	int		x;
	int		y;

	x = 0;
	while (x < mlx->set->s_width)
	{
		y = 0;
		while (y < mlx->set->s_height)
		{
			if (y < mlx->set->s_height / 2)
				my_mlx_pixel_put(mlx, x, y, mlx->set->ceiling_c);
			else
				my_mlx_pixel_put(mlx, x, y, mlx->set->floor_c);
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
