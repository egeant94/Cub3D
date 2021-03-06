/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:52:04 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 09:44:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fix_player_pos(t_camera *cam)
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
		cam->player_y += 1;
	}
	if (cam->player_dy <= 0)
	{
		cam->player_dy += 1;
		cam->player_y -= 1;
	}
}

void	change_player_pos(t_camera *cam, int **world_map, t_coord temp)
{
	int ret;

	ret = world_map[(int)(cam->player_y + cam->player_dy + temp.y)]
				[(int)(cam->player_x + cam->player_dx + temp.x)];
	if (ret != 1 && ret != -2)
	{
		cam->player_dx += temp.x;
		cam->player_dy += temp.y;
		return (fix_player_pos(cam));
	}
	ret = world_map[(int)(cam->player_y + cam->player_dy + temp.y)]
				[(int)(cam->player_x + cam->player_dx)];
	if (ret != 1 && ret != -2)
	{
		cam->player_dy += temp.y;
		return (fix_player_pos(cam));
	}
	ret = world_map[(int)(cam->player_y + cam->player_dy)]
				[(int)(cam->player_x + cam->player_dx + temp.x)];
	if (ret != 1 && ret != -2)
	{
		cam->player_dx += temp.x;
		return (fix_player_pos(cam));
	}
}

void	move(t_camera *cam, int **world_map, int dir)
{
	t_coord	temp;
	float	temp_angle;

	temp_angle = cam->beta_ang;
	if (dir == 2)
		temp_angle += 90;
	if (dir == -2)
		temp_angle -= 90;
	if (dir == -2 || dir == 2)
		dir = 1;
	temp.x = fabs(cos(angle_to_quadrant(&temp_angle, cam)
	* M_PI / 180.0)) * dir * cam->tile_step_x / cam->movement_speed * SPEED;
	temp.y = fabs(sin(angle_to_quadrant(&temp_angle, cam)
	* M_PI / 180.0)) * dir * cam->tile_step_y / cam->movement_speed * SPEED;
	change_player_pos(cam, world_map, temp);
}

void	init_movements(t_movements *move)
{
	move->forward = 0;
	move->backward = 0;
	move->left = 0;
	move->right = 0;
	move->cam_left = 0;
	move->cam_right = 0;
}
