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
#define screenWidth 1920
#define screenHeight 1080
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

int		angle_to_quadrant(int angle)
{
	if (angle < 90 && angle > 0)
	{
		tile_step_x = 1;
		tile_step_y = -1;
		
		return (angle);
	}
	if (angle < 180 && angle > 90)
		return (90 - (angle - 90));
	if (angle < 270 && angle > 180)
		return (angle - 180);
	if (angle < 360 && angle > 270)
		return (90 - (angle - 270)

void calculate_first_frame(t_mlx_data *mlx, t_camera *cam, int worldMap[6][6])
{
	int i;
	i = 0;
	cam->theta_ang = cam->beta_ang + (FOV / 2);
	if (cam->theta_ang > 90)
		cam->theta_ang +=
			while (i < screenWidth)
		{
			cam->theta_ang -= ((float)FOV / (float)screenWidth);
			printf("%.2f\n", cam->theta_ang);
			i++;
		}
	if (worldMap[0][0])
		(void)mlx;
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
