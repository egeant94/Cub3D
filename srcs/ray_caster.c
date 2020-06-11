/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:45:24 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 10:24:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int		frame_render(t_mlx_data *mlx, t_camera *cam, int **world_map, int save)
{
	cam->plan_size = tan((FOV / 2) * M_PI / 180.0);
	mlx->img = mlx_new_image(mlx->mlx, mlx->set->s_width, mlx->set->s_height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
								&mlx->line_length, &mlx->endian);
	if ((cam->dists = dist_buffer(mlx->set)) == 0)
		return (-1);
	if (ray_looper(mlx, cam, cam->plan_size, world_map) == -1)
		return (-1);
	if (display_sprites(mlx, cam) == -1)
		return (-1);
	if (save == 1)
		return (0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	free_all(mlx, cam);
	return (0);
}

int		ray_looper(t_mlx_data *mlx, t_camera *cam,
					float plan_size, int **world_map)
{
	int		column;
	float	quad_theta;
	float	cam_plan;

	column = 0;
	cam_plan = plan_size;
	while (column < mlx->set->s_width)
	{
		cam->theta_ang = cam->beta_ang + atan(cam_plan) * 180.0 / M_PI;
		quad_theta = angle_to_quadrant(&cam->theta_ang, cam);
		cam->dists[column] = min_ray_dist(cam, world_map, quad_theta);
		if (cam->dists[column] == -2)
			return (-1);
		print_vertical_line(mlx, column, cam->dists[column]);
		cam_plan = cam_plan - ((plan_size / (mlx->set->s_width - 1)) * 2);
		column++;
	}
	return (0);
}

float	min_ray_dist(t_camera *cam, int **world_map, float angle)
{
	float hor_dist;
	float ver_dist;
	float rad_angle;

	rad_angle = angle * M_PI / 180.0;
	first_int(cam, rad_angle, &cam->x_intercept, &cam->y_intercept);
	if (hit_wall(cam, rad_angle, world_map) == -2)
		return (-2);
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
	cam->h_o_v = 2;
	return (ver_dist * cos(fabs(quadrant_to_angle(&angle, cam) -
			cam->beta_ang) * M_PI / 180));
}

int		hit_wall(t_camera *cam, float rad, int **world_map)
{
	int		x_check;

	cam->x_intercept.x = round(cam->x_intercept.x);
	if (cam->tile_step_x == 1)
		x_check = 0;
	else
		x_check = -1;
	while (cam->x_intercept.x + x_check >= 0 &&
			cam->x_intercept.x + x_check < cam->max_x &&
			cam->x_intercept.y >= 0 && cam->x_intercept.y < cam->max_y)
	{
		if (world_map[(int)cam->x_intercept.y]
			[(int)cam->x_intercept.x + x_check] == 1)
			break ;
		if (world_map[(int)cam->x_intercept.y]
			[(int)cam->x_intercept.x + x_check] == 2)
			if (add_sprite(cam, (int)cam->x_intercept.x + x_check,
				(int)cam->x_intercept.y) == -1)
				return (-2);
		cam->x_intercept.x += cam->tile_step_x;
		cam->x_intercept.y += tan(rad) * cam->tile_step_y;
	}
	if (hit_hor(cam, rad, world_map) == -2)
		return (-2);
	return (0);
}

int		hit_hor(t_camera *cam, float rad, int **world_map)
{
	int		y_check;

	cam->y_intercept.y = round(cam->y_intercept.y);
	if (cam->tile_step_y == 1)
		y_check = 0;
	else
		y_check = -1;
	while (cam->y_intercept.x >= 0 && cam->y_intercept.x < cam->max_x &&
			cam->y_intercept.y + y_check >= 0 &&
			cam->y_intercept.y + y_check < cam->max_y)
	{
		if (world_map[(int)cam->y_intercept.y + y_check]
			[(int)cam->y_intercept.x] == 1)
			break ;
		if (world_map[(int)cam->y_intercept.y + y_check]
			[(int)cam->y_intercept.x] == 2)
			if ((add_sprite(cam, (int)cam->y_intercept.x,
						(int)cam->y_intercept.y + y_check)) == -1)
				return (-2);
		cam->y_intercept.x += 1 / tan(rad) * cam->tile_step_x;
		cam->y_intercept.y += cam->tile_step_y;
	}
	return (0);
}
