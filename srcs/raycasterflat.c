/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasterflat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osboxes <osboxes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:18:23 by osboxes           #+#    #+#             */
/*   Updated: 2020/02/17 09:24:07 by osboxes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"
#define screenWidth 3
#define screenHeight 100
#define map_max 6
#define FOV 90
typedef struct s_camera
{
	int player_x;
	int player_y;
	float player_dx;
	float player_dy;
	float dir_x;
	float dir_y;
	float beta_ang;
	float theta_ang;
	float x_intercept;
	float y_intercept;
	float x_step;
	float y_step;
	int tile_step_x;
	int tile_step_y;
} t_camera;

typedef struct s_mlx_data
{
	void *mlx;
	void *win;
	void *img;
	void *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_mlx_data;

typedef struct s_coordinates
{
	float x;
	float y;
} t_coordinates;

void init_camera(t_camera *cam)
{
	cam->player_x = 4;
	cam->player_y = 3;
	cam->player_dx = 0.5;
	cam->player_dy = 0.5;
	cam->dir_x = 0;
	cam->dir_y = -1;
	cam->beta_ang = 90;
	cam->theta_ang = 0;
	cam->x_intercept = 0;
	cam->y_intercept = 0;
	cam->x_step = 0;
	cam->y_step = 0;
	cam->tile_step_x = 0;
	cam->tile_step_y = 0;
}

void my_mlx_pixel_put(t_mlx_data *mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void angle_over_under(float *angle)
{
	if (*angle >= 360)
		(*angle) = *angle - 360;
	if (*angle < 0)
		(*angle) = 360 + (*angle);
}

float angle_to_quadrant(float *angle, t_camera *cam)
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

float min_ray_dist(t_camera *cam, int worldMap[6][6], float angle)
{
	t_coordinates x_intercept;
	t_coordinates y_intercept;
	float hor_dist;
	float ver_dist;
	float rad_angle;

	rad_angle = angle * M_PI / 180;
	x_intercept.x = cam->player_x + cam->player_dx;
	x_intercept.y = cam->player_y + cam->player_dy;

	if (cam->tile_step_x == 1)
	{
		x_intercept.x += 1.0 - cam->player_dx;
		x_intercept.y += (1.0 - cam->player_dx) * tan(rad_angle) * cam->tile_step_y;
	}
	else
	{
		x_intercept.x += (- cam->player_dx);
		x_intercept.y += cam->player_dx * tan(rad_angle) * cam->tile_step_y;
	}
	while (x_intercept.x < map_max && x_intercept.y < map_max && x_intercept.x >= 0 && x_intercept.y >= 0)
	{
		if (cam->tile_step_x == - 1)
		{
			if (worldMap[(int)x_intercept.y][(int)x_intercept.x - 1] == 1)
				break ;
		}
		else
			if (worldMap[(int)x_intercept.y][(int)x_intercept.x] == 1)
				break ;
		x_intercept.x += cam->tile_step_x;
		x_intercept.y += cam->tile_step_x * tan(rad_angle);
	}
	y_intercept.x = cam->player_x + cam->player_dx;
	y_intercept.y = cam->player_y + cam->player_dy;

	if (cam->tile_step_y == 1)
	{
		y_intercept.x += (1.0 - cam->player_dy) / tan(rad_angle) * cam->tile_step_x;
		y_intercept.y += 1.0 - cam->player_dy;
	}
	else
	{
		y_intercept.x += (cam->player_dy) / tan(rad_angle) * cam->tile_step_x;
		y_intercept.y += (-cam->player_dy);
	}
	while (y_intercept.x < map_max && y_intercept.y < map_max && y_intercept.x >= 0 && y_intercept.y >= 0)
	{
		if (cam->tile_step_y == - 1)
		{
			if (worldMap[(int)y_intercept.y - 1][(int)y_intercept.x] == 1)
				break ;
		}
		else
			if (worldMap[(int)y_intercept.y][(int)y_intercept.x] == 1)
				break ;
		y_intercept.x += cam->tile_step_y / tan(rad_angle);
		y_intercept.y += cam->tile_step_y;
	}
	if (worldMap[0][0] == 1)
		(void)worldMap;
	hor_dist = sqrt(pow(x_intercept.x - (cam->player_x + cam->player_dx), 2) + pow(x_intercept.y - (cam->player_y + cam->player_dy), 2));
	ver_dist = sqrt(pow(y_intercept.x - (cam->player_x + cam->player_dx), 2) + pow(y_intercept.y - (cam->player_y + cam->player_dy), 2));
	if (hor_dist < ver_dist)
		return (hor_dist);
	else
		return (ver_dist);
}

void calculate_first_frame(t_mlx_data *mlx, t_camera *cam, int worldMap[6][6])
{
	int column;
	float quadrant_theta;

	column = 0;
	cam->theta_ang = cam->beta_ang + (FOV / 2);
	mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
								  &mlx->line_length, &mlx->endian);
	while (column < screenWidth)
	{
		quadrant_theta = angle_to_quadrant(&cam->theta_ang, cam);
		printf("%7.2f ", cam->theta_ang);
		printf("%f\n", min_ray_dist(cam, worldMap, quadrant_theta));
		// min_ray_dist(cam, worldMap, quadrant_theta);
		cam->theta_ang -= ((float)FOV / ((float)screenWidth - 1.0));
		column++;
	}
}

int main(void)
{
	t_camera cam;
	t_mlx_data mlx;
	int worldMap[6][6] =
		{
			{1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 1},
			{1, 0, 1, 0, 0, 1},
			{1, 0, 0, 0, 3, 1},
			{1, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1}};

	init_camera(&cam);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "raycasterflat");
	calculate_first_frame(&mlx, &cam, worldMap);
	mlx_loop(mlx.mlx);
}
