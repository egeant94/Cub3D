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
typedef struct	s_camera
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
}				t_camera;

int	init_camera(t_camera *cam)
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

int main(void)
{
	t_camera cam;

	int worldMap[6][6] =
	{
		{1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 3, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1}
	};
	init_camera(&cam);
	
