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
#define FOV 80 //between 0 and 180
#define WALL_HEIGHT 0.5
#define SPEED_M 0.1
typedef struct s_coordinates
{
	float x;
	float y;
} t_coord;

typedef struct s_camera
{
	int player_x;
	int player_y;
	float player_dx;
	float player_dy;
	float h_o_v;
	float beta_ang;
	float theta_ang;
	t_coord x_intercept;
	t_coord y_intercept;
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
	int **worldMap;
	t_camera *cam;
} t_mlx_data;

void init_camera(t_camera *cam)
{
	cam->player_x = 4;
	cam->player_y = 2;
	cam->player_dx = 0.616199;
	cam->player_dy = 0.600000;
	cam->h_o_v = 0;
	cam->beta_ang = 174;
	cam->theta_ang = 0;
	cam->x_intercept.x = 0;
	cam->x_intercept.y = 0;
	cam->y_intercept.x = 0;
	cam->y_intercept.y = 0;
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
		x_inter->x += (- cam->player_dx);
		x_inter->y += cam->player_dx * tan(rad) * cam->tile_step_y;
	}
	y_inter->x = cam->player_x + cam->player_dx;
	y_inter->y = cam->player_y + cam->player_dy;
	if (cam->tile_step_y == 1)
	{
		y_inter->x += (1.0 - cam->player_dy) / tan(rad) * (float)cam->tile_step_x;
		y_inter->y += 1.0 - cam->player_dy;
	}
	else
	{
		y_inter->x += (cam->player_dy) / tan(rad) * cam->tile_step_x;
		y_inter->y += (-cam->player_dy);
	}
}

void	hit_wall(t_camera *cam, float rad, int **worldMap)
{
	while (	cam->x_intercept.x >= 0 && cam->x_intercept.x < map_max &&
			cam->x_intercept.y >= 0 && cam->x_intercept.y < map_max)
	{
		cam->x_intercept.x += cam->tile_step_x;
		cam->x_intercept.y += tan(rad) * cam->tile_step_y;
	}
	while (	cam->y_intercept.x >= 0 && cam->y_intercept.x < map_max &&
			cam->y_intercept.y >= 0 && cam->y_intercept.y < map_max)
	{
		cam->y_intercept.x += 1 / tan(rad) * cam->tile_step_x;
		cam->y_intercept.y += cam->tile_step_y;
	}
	if (worldMap[0][0] == 0)
		return ;
}

float min_ray_dist(t_camera *cam, int **worldMap, float angle)
{
	float hor_dist;
	float ver_dist;
	float rad_angle;

	rad_angle = angle * M_PI / 180.0;
	first_int(cam, rad_angle, &cam->x_intercept, &cam->y_intercept);
	hit_wall(cam, rad_angle, worldMap);
	hor_dist = sqrt(pow(cam->x_intercept.x - (cam->player_x + cam->player_dx), 2) + pow(cam->x_intercept.y - (cam->player_y + cam->player_dy), 2));
	ver_dist = sqrt(pow(cam->y_intercept.x - (cam->player_x + cam->player_dx), 2) + pow(cam->y_intercept.y - (cam->player_y + cam->player_dy), 2));
	if (hor_dist < ver_dist)
	{
		cam->h_o_v = 1;
		// return(hor_dist);
		return (hor_dist * cos(fabs(quadrant_to_angle(&angle, cam) - cam->beta_ang) * M_PI / 180));
	}
	else
	{
		cam->h_o_v = 2;
		// return(ver_dist);
		return(ver_dist * cos(fabs(quadrant_to_angle(&angle, cam) - cam->beta_ang) * M_PI / 180));
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

void calculate_first_frame(t_mlx_data *mlx, t_camera *cam, int **worldMap)
{
	int column;
	float quadrant_theta;
	float	cam_plan;
	float	plan_size;

	column = 0;
	// cam->theta_ang = cam->beta_ang + (FOV / 2);
	plan_size = tan((FOV / 2) * M_PI / 180.0);
	cam_plan = plan_size;
	mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
								  &mlx->line_length, &mlx->endian);
	while (column < screenWidth)
	{
		cam->theta_ang = cam->beta_ang + atan(cam_plan) * 180.0 / M_PI;
		quadrant_theta = angle_to_quadrant(&cam->theta_ang, cam);
		print_vertical_line(mlx, column, min_ray_dist(cam, worldMap, quadrant_theta), *cam);
		cam_plan = cam_plan - ((plan_size / (screenWidth - 1)) * 2);
		column++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void		fix_player_pos(t_camera *cam)
{
	if (cam->player_dx >= 1)
	{
		cam->player_dx -= 1;
		cam->player_x += 1;
	}
	if (cam->player_dx <= 0)
	{
		cam->player_dx += 1;
		cam->player_x -= 1;
	}
	if (cam->player_dy >= 1)
	{
		cam->player_dy -= 1;
		cam->player_y+= 1;
	}
	if (cam->player_dy <= 0)
	{
		cam->player_dy += 1;
		cam->player_y -= 1;
	}
}
	
void		move(t_camera *cam, int **worldMap, int dir)
{
	t_coord	temp;
	float			temp_angle;

	temp_angle = cam->beta_ang;
	if (dir == 2)
	{
		dir = 1;
		temp_angle += 90;
	}
	if (dir == -2)
	{
		dir = 1;
		temp_angle -= 90;
	}	
	temp.x = fabs(cos(angle_to_quadrant(&temp_angle, cam) * M_PI / 180.0) * SPEED_M) * dir * cam->tile_step_x;
	temp.y = fabs(sin(angle_to_quadrant(&temp_angle, cam) * M_PI / 180.0) * SPEED_M) * dir * cam->tile_step_y;
	if (worldMap[(int)(cam->player_y + cam->player_dy + temp.y)][(int)(cam->player_x + cam->player_dx + temp.x)])
		return ;
	cam->player_dx += temp.x;
	cam->player_dy += temp.y;
	fix_player_pos(cam);
}

int	camera(int keycode, t_mlx_data *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	if (keycode == 119 || keycode == 122)
		move(mlx->cam, mlx->worldMap, 1); // z or w, up movment
	if (keycode == 115)
		move(mlx->cam, mlx->worldMap, -1); // s, down movment
	if (keycode == 97 || keycode == 113)
		move(mlx->cam, mlx->worldMap, 2); // q or a, left movement
	if (keycode == 100)
		move(mlx->cam, mlx->worldMap, -2); // d, right movement
	if (keycode == 65361) //left arrow, camera moving to the left
		mlx->cam->beta_ang += 4;
	if (keycode == 65363) //right arrow, camera moving to the right
		mlx->cam->beta_ang -= 4;
	printf("%f, %f\n", mlx->cam->player_x + mlx->cam->player_dx, mlx->cam->player_y + mlx->cam->player_dy);
	angle_over_under(&mlx->cam->beta_ang);
	calculate_first_frame(mlx, mlx->cam, mlx->worldMap);
	return (1);
}

int		**create_map(void)
{
	int			**map;
	int			i;
	int			y;

	map = malloc(sizeof(int *) * 6);
	i = 0;
	while (i < 6)
	{
		map[i] = malloc(sizeof(int) * 6);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		y = 0;
		while (y < 6)
		{
			map[i][y] = 0;
			y++;
		}
		i++;
	}
	i = 0;
	while (i < 6)
	{
		map[0][i] = 1;
		map[5][i] = 1;
		map[i][0] = 1;
		map[i][5] = 1;
		i++;
	}
	map[2][2] = 1;
	return (map);
}

int main(void)
{
	t_camera cam;
	t_mlx_data mlx;

	mlx.worldMap = create_map();
	int i = 0, y = 0;
	while (i < 6)
	{
		y = 0;
		while (y < 6)
		{
			printf("%d, ", mlx.worldMap[i][y]);
			y++;
		}
		printf("\n");
		i++;
	}
	init_camera(&cam);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "raycasterflat");
	calculate_first_frame(&mlx, &cam, mlx.worldMap);
	mlx.cam = &cam;
	mlx_hook(mlx.win, 2, 1L<<0, camera, &mlx); 
	mlx_loop(mlx.mlx);
}
