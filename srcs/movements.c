/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:52:04 by user42            #+#    #+#             */
/*   Updated: 2020/04/27 22:52:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

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
	if (world_map[(int)(cam->player_y + cam->player_dy + temp.y)]
				[(int)(cam->player_x + cam->player_dx + temp.x)] != 1)
	{
		cam->player_dx += temp.x;
		cam->player_dy += temp.y;
		fix_player_pos(cam);
		return ;
	}
	if (world_map[(int)(cam->player_y + cam->player_dy + temp.y)]
				[(int)(cam->player_x + cam->player_dx)] != 1)
	{
		cam->player_dy += temp.y;
		fix_player_pos(cam);
		return ;
	}
	if (world_map[(int)(cam->player_y + cam->player_dy)]
				[(int)(cam->player_x + cam->player_dx + temp.x)] != 1)
	{
		cam->player_dx += temp.x;
		fix_player_pos(cam);
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
			* M_PI / 180.0) * SPEED_M) * dir * cam->tile_step_x;
	temp.y = fabs(sin(angle_to_quadrant(&temp_angle, cam)
			* M_PI / 180.0) * SPEED_M) * dir * cam->tile_step_y;
	change_player_pos(cam, world_map, temp);
}

int		camera(int keycode, t_mlx_data *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	if (keycode == 119 || keycode == 122)
		move(mlx->cam, mlx->world_map, 1);
	if (keycode == 115)
		move(mlx->cam, mlx->world_map, -1);
	if (keycode == 97 || keycode == 113)
		move(mlx->cam, mlx->world_map, 2);
	if (keycode == 100)
		move(mlx->cam, mlx->world_map, -2);
	if (keycode == 65361)
		mlx->cam->beta_ang += 4;
	if (keycode == 65363)
		mlx->cam->beta_ang -= 4;
	angle_over_under(&mlx->cam->beta_ang);
	calculate_first_frame(mlx, mlx->cam, mlx->world_map);
	return (1);
}
