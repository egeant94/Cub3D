/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:45:24 by user42            #+#    #+#             */
/*   Updated: 2020/05/25 15:39:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

t_coord		hit_wall_before(float *intercept, t_coord hit)
{
	*intercept = -1;
	return (hit);
}

t_coord		sprite_ver(t_camera *cam, float rad, int **world_map)
{
	t_coord hit;
	int		x_check;

	hit.x = round(cam->x_intercept.x);
	hit.y = cam->x_intercept.y;
	if (cam->tile_step_x == 1)
		x_check = 0;
	else
		x_check = -1;
	while (hit.x + x_check >= 0 && hit.x + x_check < MAP_MAX &&
			hit.y >= 0 && hit.y < MAP_MAX)
	{
		if (world_map[(int)hit.y][(int)hit.x + x_check] == 1)
			return (hit_wall_before(&cam->x_intercept.x, hit));
		if (world_map[(int)hit.y][(int)hit.x + x_check] == 2)
			return (hit);
		hit.x += cam->tile_step_x;
		hit.y += tan(rad) * cam->tile_step_y;
	}
	cam->x_intercept.x = -1;
	return (hit);
}

t_coord		sprite_hor(t_camera *cam, float rad, int **world_map)
{
	int		y_check;
	t_coord hit;

	hit.y = round(cam->y_intercept.y);
	hit.x = cam->y_intercept.x;
	if (cam->tile_step_y == 1)
		y_check = 0;
	else
		y_check = -1;
	while (hit.x >= 0 && hit.x < MAP_MAX && hit.y + y_check >= 0 &&
			hit.y + y_check < MAP_MAX)
	{
		if (world_map[(int)hit.y + y_check][(int)hit.x] == 1)
			return (hit_wall_before(&cam->y_intercept.x, hit));
		if (world_map[(int)hit.y + y_check][(int)hit.x] == 2)
			return (hit);
		hit.x += 1 / tan(rad) * cam->tile_step_x;
		hit.y += cam->tile_step_y;
	}
	cam->y_intercept.x = -1;
	return (hit);
}

int			is_sprite_here(t_coord hv, t_coord ho)
{
	if (hv.x == -1 && ho.x == -1)
		return (1);
	return (0);
}
	
t_coord		hit_sprite(t_camera *cam, float rad, int **world_map)
{
	t_coord ver_hit;
	t_coord hor_hit;
	float	ver_dist;
	float	hor_dist;

	ver_hit = sprite_ver(cam, rad, world_map);
	hor_hit = sprite_hor(cam, rad, world_map);
	ver_dist = sqrt(pow(ver_hit.x -
			(cam->player_x + cam->player_dx), 2) +
			pow(ver_hit.y - (cam->player_y + cam->player_dy), 2));
	hor_dist = sqrt(pow(hor_hit.x -
		(cam->player_x + cam->player_dx), 2) +
		pow(hor_hit.y - (cam->player_y + cam->player_dy), 2));
	if (hor_dist < ver_dist)
	{
		if (cam->y_intercept.x == -1)
			hor_hit.x = -1;
		cam->h_o_v = 1;
		return (hor_hit);
	}
	else
	{
		if (cam->x_intercept.x == -1)
			ver_hit.x = -1;
		cam->h_o_v = 2;
		return (ver_hit);
	}
}
	
t_coord	ray_sprite(t_camera *cam, int **world_map, float angle)
{
	float	rad_angle;
	
	rad_angle = angle * M_PI / 180.0;
	first_int(cam, rad_angle, &cam->x_intercept, &cam->y_intercept);
	return (hit_sprite(cam, rad_angle, world_map));
}

float	width_deductor_2(t_coord hit, t_camera *cam)
{
	if (hit.y < cam->player_y + cam->player_dy)
	{
		if (cam->h_o_v == 1)
			return ((1 + (hit.x - (int)hit.x)) / 2);
		else
			return ((hit.y - (int)hit.y) / 2);
	}
	else
	{
		if (cam->h_o_v == 1)
			return ((1 - (hit.x - (int)hit.x)) / 2);
		else
			return ((1 + (hit.y - (int)hit.y)) / 2);
	}
}

float	check_right_angle(t_coord hit, t_camera *cam, float width)
{
	if (cam->beta_ang == 0 || cam->beta_ang == 360)
		width = hit.y - (int)hit.y;
	if (cam->beta_ang == 180)
		width = 1 - (hit.y - (int)hit.y);
	if (cam->beta_ang == 90)
		width = hit.x - (int)hit.x;
	if (cam->beta_ang == 270)
		width = 1 - (hit.x - (int)hit.x);
	return (width);
}

float	width_deductor(t_coord hit, t_camera *cam)
{
	float	width;

	if (hit.x < cam->player_x + cam->player_dx)
	{
		if (hit.y < cam->player_y + cam->player_dy)
		{
			if (cam->h_o_v == 1)
				width = (hit.x - (int)hit.x) / 2;
			else
				width = (1 + (1 - (hit.y - (int)hit.y))) / 2;
		}
		else
		{
			if (cam->h_o_v == 1)
				width = (1 + (1 - (hit.x - (int)hit.x))) / 2;
			else
				width = (1 - (hit.y - (int)hit.y)) / 2;
		}
	}
	else
		width = width_deductor_2(hit, cam);
	return (check_right_angle(hit, cam, width));
}

void	vertical_sprite_line(float dist, float width, t_mlx_data *mlx, int x)
{
	float		y;
	float		wall_offset;
	float		tex_y;
	t_texture	*tex;

	tex = &mlx->set->sprite;
	// width = 0;
	wall_offset = wall_offseter(dist, tex, &tex_y, mlx);
	y = init_y(wall_offset);
	while (y < mlx->set->s_height && y < mlx->set->s_height - wall_offset)
	{
		tex_y += inc_tex_y(wall_offset, tex, mlx, dist);
		my_mlx_pixel_put(mlx, x, y,
			my_mlx_pixel_reverse(tex, width * tex->width, (int)tex_y));
		y++;
	}
}

float	dist_calc(t_coord hit, t_camera *cam)
{
	float	dist;
	float	rad_ang;
	float	rad_beta;

	rad_beta = cam->beta_ang / 180 * M_PI;
	dist = sqrt(pow(hit.x - (cam->player_x + cam->player_dx), 2) +
			pow(hit.y - (cam->player_y + cam->player_dy), 2));
	rad_ang = acos(fabs((cam->player_x + cam->player_dx) - hit.x) / dist);
	if (cam->player_x + cam->player_dx > hit.x
		&& cam->player_y + cam->player_dy > hit.y) 
		rad_ang = M_PI - (rad_ang + rad_beta);
	else if (cam->player_y + cam->player_dy < hit.y)
		rad_ang = M_PI - rad_beta + rad_ang;
	else if (cam->player_x + cam->player_dx < hit.x
			&& cam->player_y + cam->player_dy < hit.y)
		rad_ang = 2 * M_PI - (rad_beta + rad_ang);
	else
		rad_ang = rad_beta - rad_ang;
	dist = fabs(dist * cos(rad_ang));
	return (dist);
}

t_coord		sprite_center(t_coord hit, t_camera *cam)
{
	t_coord center;
	int		x_check;
	int		y_check;

	if (cam->tile_step_x == -1 && cam->h_o_v == 2)
		x_check = -1;
	else
		x_check = 0;
	if (cam->tile_step_y == -1 && cam->h_o_v == 1)
		y_check = -1;
	else
		y_check = 0;
	center.x = hit.x - (hit.x - (int)hit.x) + 0.5 + x_check;
	center.y = hit.y - (hit.y - (int)hit.y) + 0.5 + y_check;
	return (center);
}	

void	print_sprite(t_mlx_data *mlx, int x, t_coord hit, t_camera *cam)
{
	float	width;
	t_coord	center;
	// t_coord	sprite_1;
	// float	rad;

	if (hit.x == -1)
		return ;
	width = width_deductor(hit, cam);
	center = sprite_center(hit, cam);
	// rad = cam->beta_ang + 90;
	// rad = rad / 180 * M_PI;
	// sprite_1.x = center.x + (cos(rad) * 0.5);
	// sprite_1.y = center.y + (sin(rad) * 0.5);
	// printf("hit x: %f y: %f ", hit.x, hit.y);
	// hit.x = (1 - t) * sprite_1.x + (t * center.x);
	// hit.y = (1 - t) * sprite_1.y + (t * center.y);
	// printf("t: %f, hov : %f\n", t, cam->h_o_v);
	// print_vertical_line(mlx, x, dist_calc(hit, cam), *cam);
	printf("width : %f\n", width);
	vertical_sprite_line(dist_calc(center, cam), width, mlx, x);
	
}

int		add_sprite(t_camera *cam, int x, int y)
{
	t_coord		*new_sprites;
	int			i;
	int			q;

	i = 0;
	while (cam->sprites != 0 && cam->sprites[i].x != -1)
	{
		if (x == cam->sprites[i].x && y == cam->sprites[i].y)
			return (0);
		i++;
	}
	if ((new_sprites = malloc((i + 2) * sizeof(*new_sprites))) == 0)
		return (-1);
	q = 0;
	while (q < i)
	{
		new_sprites[q] = cam->sprites[q];
		q++;
	}
	new_sprites[q].x = x;
	new_sprites[q].y = y;
	new_sprites[q + 1].x = -1;
	free(cam->sprites);
	cam->sprites = new_sprites;
	return (0);
}

float	*dist_buffer(t_settings *set)
{
	float	*buffer;

	buffer = malloc((set->s_width + 1) * sizeof(float));
	buffer[set->s_width] = -1;
	return (buffer);
}

void	print_sprites(t_mlx_data *mlx, t_camera *cam)
{
	int i;

	i = 0;
	(void)mlx;
	while (cam->sprites != 0 && cam->sprites[i].x != -1)
	{
		ft_printf("Sprite num %d : x = %d, y = %d\n", i + 1, (int)cam->sprites[i].x, (int)cam->sprites[i].y);
		i++;
	}
}

int		ray_looper(t_mlx_data *mlx, t_camera *cam, float plan_size, int **world_map)
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
		print_vertical_line(mlx, column, cam->dists[column], *cam);						
		cam_plan = cam_plan - ((plan_size / (mlx->set->s_width - 1)) * 2);
		column++;
	}
	return (0);
}

int		frame_render(t_mlx_data *mlx, t_camera *cam, int **world_map)
{
	float	plan_size;

	plan_size = tan((FOV / 2) * M_PI / 180.0);
	mlx->img = mlx_new_image(mlx->mlx, mlx->set->s_width, mlx->set->s_height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
								&mlx->line_length, &mlx->endian);
	if ((cam->dists = dist_buffer(mlx->set)) == 0)
		return (-1);
	if (ray_looper(mlx, cam, plan_size, world_map) == -1)
		return (-1);
	print_sprites(mlx, cam);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	free_all(mlx, cam);
	return (0);
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

int		hit_hor(t_camera *cam, float rad, int **world_map)
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

int		hit_wall(t_camera *cam, float rad, int **world_map)
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
