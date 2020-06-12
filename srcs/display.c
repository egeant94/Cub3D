/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:51:03 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 11:33:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_mlx_data *mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	print_vline_2(t_mlx_data *mlx, int x, float dist, float tex_y)
{
	int			y;
	t_texture	*tex;

	tex = nwse_tex(*(mlx->cam), mlx);
	y = 0;
	while (y < mlx->set->s_height)
	{
		if (y < init_y(mlx->cam->wall_offset) && y < mlx->set->s_height / 2)
			my_mlx_pixel_put(mlx, x, y, mlx->set->ceiling_c);
		else if (y > (mlx->set->s_height - mlx->cam->wall_offset))
			my_mlx_pixel_put(mlx, x, y, mlx->set->floor_c);
		else
		{
			if (mlx->cam->h_o_v == 1)
				my_mlx_pixel_put(mlx, x, y, my_mlx_pixel_reverse(tex,
					(mlx->cam->y_intercept.x - (int)mlx->cam->y_intercept.x)
					* tex->width, (int)tex_y));
			if (mlx->cam->h_o_v == 2)
				my_mlx_pixel_put(mlx, x, y, my_mlx_pixel_reverse(tex,
					(mlx->cam->x_intercept.y - (int)mlx->cam->x_intercept.y)
					* tex->width, (int)tex_y));
			tex_y += inc_tex_y(mlx->cam->wall_offset, tex, mlx, dist);
		}
		y++;
	}
}

void	print_vertical_line(t_mlx_data *mlx, int x, float dist)
{
	float		tex_y;
	t_texture	*tex;

	if (dist == -1)
		return ;
	tex = nwse_tex(*(mlx->cam), mlx);
	mlx->cam->wall_offset = wall_offseter(dist, tex, &tex_y, mlx);
	print_vline_2(mlx, x, dist, tex_y);
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
