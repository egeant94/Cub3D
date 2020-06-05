/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:51:03 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 11:06:13 by user42           ###   ########.fr       */
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
	float		wall_offset;
	float		tex_y;
	t_texture	*tex;

	if (dist == -1)
		return ;
	tex = nwse_tex(cam, mlx);
	wall_offset = wall_offseter(dist, tex, &tex_y, mlx);
	y = 0;
	while (y < mlx->set->s_height)
	{
		if (y < init_y(wall_offset) && y < mlx->set->s_height / 2)
			my_mlx_pixel_put(mlx, x, y, mlx->set->ceiling_c);
		else if (y > (mlx->set->s_height - wall_offset))
			my_mlx_pixel_put(mlx, x, y, mlx->set->floor_c);
		else
		{
			tex_y += inc_tex_y(wall_offset, tex, mlx, dist);
			if (cam.h_o_v == 1)
				my_mlx_pixel_put(mlx, x, y, my_mlx_pixel_reverse(
					tex, (cam.y_intercept.x - (int)cam.y_intercept.x)
					* tex->width, (int)tex_y));
			if (cam.h_o_v == 2)
				my_mlx_pixel_put(mlx, x, y, my_mlx_pixel_reverse(
					tex, (cam.x_intercept.y - (int)cam.x_intercept.y)
					* tex->width, (int)tex_y));
		}
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
	cam->player_x = -1;
	cam->player_y = -1;
	cam->player_dx = 0.51;
	cam->player_dy = 0.51;
	cam->h_o_v = 0;
	cam->beta_ang = 0;
	cam->theta_ang = 0;
	cam->x_intercept.x = 0;
	cam->x_intercept.y = 0;
	cam->y_intercept.x = 0;
	cam->y_intercept.y = 0;
	cam->x_step = 0;
	cam->y_step = 0;
	cam->tile_step_x = 0;
	cam->tile_step_y = 0;
	cam->sprites = 0;
	cam->sprite_dists = 0;
	cam->dists = 0;
	cam->max_x = 0;
	cam->max_y = 0;
}
