/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:17:56 by user42            #+#    #+#             */
/*   Updated: 2020/06/18 12:29:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	first_int(t_camera *cam, float rad, t_coord *x_inter, t_coord *y_inter)
{
	x_inter->x = cam->player_x + cam->player_dx;
	x_inter->y = cam->player_y + cam->player_dy;
	if (cam->tile_step_x == 1)
	{
		x_inter->x += 1.0 - cam->player_dx;
		x_inter->y += (1.0 - cam->player_dx) * tan(rad) * cam->tile_step_y;
	}
	else
	{
		x_inter->x += (-cam->player_dx);
		x_inter->y += cam->player_dx * tan(rad) * cam->tile_step_y;
	}
	y_inter->x = cam->player_x + cam->player_dx;
	y_inter->y = cam->player_y + cam->player_dy;
	if (cam->tile_step_y == 1)
	{
		y_inter->x += (1.0 - cam->player_dy) / tan(rad) * cam->tile_step_x;
		y_inter->y += 1.0 - cam->player_dy;
	}
	else
	{
		y_inter->x += (cam->player_dy) / tan(rad) * cam->tile_step_x;
		y_inter->y += (-cam->player_dy);
	}
}
