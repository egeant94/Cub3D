/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 17:16:34 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 13:13:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_texture	*nwse_tex(t_camera cam, t_mlx_data *mlx)
{
	if (cam.h_o_v == 2 && cam.tile_step_x == 1)
		return (&mlx->set->east);
	else if (cam.h_o_v == 2 && cam.tile_step_x == -1)
		return (&mlx->set->west);
	else if (cam.h_o_v == 1 && cam.tile_step_y == -1)
		return (&mlx->set->north);
	else
		return (&mlx->set->south);
}

float		wall_offseter(float dist, t_texture *tex, float *tex_y,
							t_mlx_data *mlx)
{
	float	wall;
	float	wall_offset;

	wall = (float)mlx->set->wall_height / dist;
	wall_offset = ((1 - wall) / 2) * mlx->set->s_height;
	*tex_y = 0;
	if (wall_offset < 0)
		*tex_y = (1 - (1 / wall)) / 2 * tex->height;
	return (wall_offset);
}

int			init_y(float wall_offset)
{
	int		y;

	if (wall_offset > 0)
		y = wall_offset;
	else
		y = 0;
	return (y);
}

float		inc_tex_y(float w_o, t_texture *tex, t_mlx_data *mlx, float dist)
{
	int tex_height;
	int s_height;

	tex_height = tex->height - 1;
	s_height = mlx->set->s_height;
	if (w_o > 0)
		return (tex_height / (s_height - w_o * 2));
	else
		return ((1 / ((float)mlx->set->wall_height / dist))
				* tex_height / s_height);
}
