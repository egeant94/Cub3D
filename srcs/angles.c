/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:49:47 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 11:35:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

void	angle_over_under(float *angle)
{
	if (*angle >= 360)
		(*angle) = *angle - 360;
	if (*angle < 0)
		(*angle) = 360 + (*angle);
}

float	angle_to_quadrant(float *angle, t_camera *cam)
{
	angle_over_under(angle);
	if (*angle <= 90 && *angle >= 0)
	{
		cam->tile_step_x = 1;
		cam->tile_step_y = -1;
		return (*angle);
	}
	if (*angle <= 180 && *angle > 90)
	{
		cam->tile_step_x = -1;
		cam->tile_step_y = -1;
		return ((90 - (*angle - 90)));
	}
	if (*angle <= 270 && *angle > 180)
	{
		cam->tile_step_x = -1;
		cam->tile_step_y = 1;
		return ((*angle - 180));
	}
	cam->tile_step_x = 1;
	cam->tile_step_y = 1;
	return ((90 - (*angle - 270)));
}

float	quadrant_to_angle(float *angle, t_camera *cam)
{
	if (cam->tile_step_x == 1 && cam->tile_step_y == -1)
		return (*angle);
	if (cam->tile_step_x == -1 && cam->tile_step_y == -1)
		return (180 - *angle);
	if (cam->tile_step_x == -1 && cam->tile_step_y == 1)
		return ((*angle + 180));
	return (360 - *angle);
}
