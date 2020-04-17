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
#define screenWidth 1000
#define screenHeight 1000
#define map_max 6
#define FOV 90
#define WALL_HEIGHT 1
typedef struct s_camera
{
	int player_x;
	int player_y;
	float player_dx;
	float player_dy;
	float h_o_v;
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
	int worldMap[6][6];
	t_camera *cam;
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
	cam->h_o_v = 0;
	cam->beta_ang = 210;
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

float min_ray_dist(t_camera *cam, int worldMap[6][6], float angle)
{
	t_coordinates x_intercept;
	t_coordinates y_intercept;
	float hor_dist;
	float ver_dist;
	float rad_angle;

	rad_angle = angle * M_PI / 180.0;
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
	hor_dist = sqrt(pow(x_intercept.x - (cam->player_x + cam->player_dx), 2) + pow(x_intercept.y - (cam->player_y + cam->player_dy), 2));
	ver_dist = sqrt(pow(y_intercept.x - (cam->player_x + cam->player_dx), 2) + pow(y_intercept.y - (cam->player_y + cam->player_dy), 2));
	if (hor_dist < ver_dist)
	{
		cam->h_o_v = 1;
		return (hor_dist * cos(fabs(quadrant_to_angle(&angle, cam) - cam->beta_ang) * M_PI / 180));
		// return (hor_dist * cos((quadrant_to_angle(&angle, cam) * M_PI / 180.00) - (cam->beta_ang * M_PI / 180.0)));
		// return ((fabs(x_intercept.x - (cam->player_x + cam->player_dx))) * cos(angle_to_quadrant(&cam->beta_ang, cam) * M_PI / 180.0)
				// + (fabs(x_intercept.y - (cam->player_y + cam->player_dy))) * sin(angle_to_quadrant(&cam->beta_ang, cam) * M_PI / 180.0));
	}
	else
	{
		cam->h_o_v = 2;
		return(ver_dist * cos(fabs(quadrant_to_angle(&angle, cam) - cam->beta_ang) * M_PI / 180));
		// return (ver_dist * cos((quadrant_to_angle(&angle, cam) * M_PI / 180.00) - (cam->beta_ang * M_PI / 180.0)));
		// return ((fabs(y_intercept.x - (cam->player_x + cam->player_dx))) * cos(angle_to_quadrant(&cam->beta_ang, cam) * M_PI / 180.0)
				// + (fabs(y_intercept.y - (cam->player_y + cam->player_dy))) * sin(angle_to_quadrant(&cam->beta_ang, cam) * M_PI / 180.0));
	}
}

void	print_vertical_line(t_mlx_data *mlx, int x, float dist, t_camera cam)
{
	float		y;
	float		wall;
	int			color;

	if (cam.h_o_v == 1 && cam.tile_step_x == 1)
		color = 0x00FF0000;
	if (cam.h_o_v == 1 && cam.tile_step_x == -1)
		color = 0x0000FF00;
	if (cam.h_o_v == 2 && cam.tile_step_y == -1)
		color = 0x000000FF;
	if (cam.h_o_v == 2 && cam.tile_step_y == 1)
		color = 0x00FFFFFF;
	y = 0;
	wall = (float)WALL_HEIGHT / dist;
	while (y < screenHeight / 2)
	{
		if ((y / (screenHeight / 2)) < wall)
		{
			my_mlx_pixel_put(mlx, x, screenHeight / 2 + y, color);
			my_mlx_pixel_put(mlx, x, screenHeight / 2 - y, color);
		}
		y++;
	}
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
		float dist = min_ray_dist(cam, worldMap, quadrant_theta);
		print_vertical_line(mlx, column, dist, *cam);
		// min_ray_dist(cam, worldMap, quadrant_theta);
		cam->theta_ang -= ((float)FOV / ((float)screenWidth - 1.0));
		column++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int	move(int keycode, t_mlx_data *mlx)
{
	(void)keycode;
	mlx->cam->beta_ang++;
	calculate_first_frame(mlx, mlx->cam, *mlx->worldMap);
}

int main(void)
{
	t_camera cam;
	t_mlx_data mlx;
	mlx.worldMap[6][6] = {
			{1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 1},
			{1, 0, 1, 0, 0, 1},
			{1, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1}};

	init_camera(&cam);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "raycasterflat");
	calculate_first_frame(&mlx, &cam, mlx.worldMap);
	mlx.cam = &cam;
	mlx_key_hook(mlx.win, move, &mlx);
	mlx_loop(mlx.mlx);
}
