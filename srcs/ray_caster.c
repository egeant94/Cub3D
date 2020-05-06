/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:45:24 by user42            #+#    #+#             */
/*   Updated: 2020/05/06 15:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

void	frame_render(t_mlx_data *mlx, t_camera *cam, int **world_map)
{
	int		column;
	float	quadrant_theta;
	float	cam_plan;
	float	plan_size;

	column = 0;
	plan_size = tan((FOV / 2) * M_PI / 180.0);
	cam_plan = plan_size;
	mlx->img = mlx_new_image(mlx->mlx, mlx->set->s_width, mlx->set->s_height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
								&mlx->line_length, &mlx->endian);
	floor_and_ceiling(mlx);
	while (column < mlx->set->s_width)
	{
		cam->theta_ang = cam->beta_ang + atan(cam_plan) * 180.0 / M_PI;
		quadrant_theta = angle_to_quadrant(&cam->theta_ang, cam);
		print_vertical_line(mlx, column,
						min_ray_dist(cam, world_map, quadrant_theta), *cam);
		cam_plan = cam_plan - ((plan_size / (mlx->set->s_width - 1)) * 2);
		column++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

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

void	hit_hor(t_camera *cam, float rad, int **world_map)
{
	int		y_check;

	cam->y_intercept.y = round(cam->y_intercept.y);
	if (cam->tile_step_y == 1)
		y_check = 0;
	else
		y_check = -1;
	while (cam->y_intercept.x >= 0 && cam->y_intercept.x < MAP_MAX &&
			cam->y_intercept.y + y_check >= 0 &&
			cam->y_intercept.y + y_check < MAP_MAX)
	{
		if (world_map[(int)cam->y_intercept.y + y_check]
			[(int)cam->y_intercept.x] == 1)
			break ;
		cam->y_intercept.x += 1 / tan(rad) * cam->tile_step_x;
		cam->y_intercept.y += cam->tile_step_y;
	}
}

void	hit_wall(t_camera *cam, float rad, int **world_map)
{
	int		x_check;

	cam->x_intercept.x = round(cam->x_intercept.x);
	if (cam->tile_step_x == 1)
		x_check = 0;
	else
		x_check = -1;
	while (cam->x_intercept.x + x_check >= 0 &&
			cam->x_intercept.x + x_check < MAP_MAX &&
			cam->x_intercept.y >= 0 && cam->x_intercept.y < MAP_MAX)
	{
		if (world_map[(int)cam->x_intercept.y]
			[(int)cam->x_intercept.x + x_check] == 1)
			break ;
		cam->x_intercept.x += cam->tile_step_x;
		cam->x_intercept.y += tan(rad) * cam->tile_step_y;
	}
	hit_hor(cam, rad, world_map);
}

float	min_ray_dist(t_camera *cam, int **world_map, float angle)
{
	float hor_dist;
	float ver_dist;
	float rad_angle;

	rad_angle = angle * M_PI / 180.0;
	first_int(cam, rad_angle, &cam->x_intercept, &cam->y_intercept);
	hit_wall(cam, rad_angle, world_map);
	ver_dist = sqrt(pow(cam->x_intercept.x -
			(cam->player_x + cam->player_dx), 2) +
			pow(cam->x_intercept.y - (cam->player_y + cam->player_dy), 2));
	hor_dist = sqrt(pow(cam->y_intercept.x -
		(cam->player_x + cam->player_dx), 2) +
		pow(cam->y_intercept.y - (cam->player_y + cam->player_dy), 2));
	if (hor_dist < ver_dist)
	{
		cam->h_o_v = 1;
		return (hor_dist * cos(fabs(quadrant_to_angle(&angle, cam) -
				cam->beta_ang) * M_PI / 180));
	}
	else
	{
		cam->h_o_v = 2;
		return (ver_dist * cos(fabs(quadrant_to_angle(&angle, cam) -
				cam->beta_ang) * M_PI / 180));
	}
}
