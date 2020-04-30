/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:52:04 by user42            #+#    #+#             */
/*   Updated: 2020/04/30 12:26:01 by user42           ###   ########.fr       */
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
			* M_PI / 180.0)) * dir * cam->tile_step_x / 20;
	temp.y = fabs(sin(angle_to_quadrant(&temp_angle, cam)
			* M_PI / 180.0)) * dir * cam->tile_step_y / 20;
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

/*119 = w, 122 = z, 97 = a, 113 = q, 115 = s, 100 = d, 65361 = left arrow, 65363 = right arrow*/
int		key_press(int keycode, t_mlx_data *mlx)
{
	if (keycode == 65307)
		quit(mlx);
	if (keycode == 119 || keycode == 122)
		mlx->move->forward = 1;
	if (keycode == 115)
		mlx->move->backward = 1;
	if (keycode == 97 || keycode == 113)
		mlx->move->left = 1;
	if (keycode == 100)
		mlx->move->right = 1;
	if (keycode == 65361)
		mlx->move->cam_left = 1;
	if (keycode == 65363)
		mlx->move->cam_right = 1;
	return (1);
}

int		key_release(int keycode, t_mlx_data *mlx)
{
	if (keycode == 65307)
		quit(mlx);
	if (keycode == 119 || keycode == 122)
		mlx->move->forward = 0;
	if (keycode == 115)
		mlx->move->backward = 0;
	if (keycode == 97 || keycode == 113)
		mlx->move->left = 0;
	if (keycode == 100)
		mlx->move->right = 0;
	if (keycode == 65361)
		mlx->move->cam_left = 0;
	if (keycode == 65363)
		mlx->move->cam_right = 0;
	return (1);
}

int		renderer(t_mlx_data *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->move->forward)
		move(mlx->cam, mlx->world_map, 1);
	if (mlx->move->backward)
		move(mlx->cam, mlx->world_map, -1);
	if (mlx->move->left)
		move(mlx->cam, mlx->world_map, 2);
	if (mlx->move->right)
		move(mlx->cam, mlx->world_map, -2);
	if (mlx->move->cam_left)
		mlx->cam->beta_ang += 3;
	if (mlx->move->cam_right)
		mlx->cam->beta_ang -= 3;
	angle_over_under(&mlx->cam->beta_ang);
	frame_render(mlx, mlx->cam, mlx->world_map);
	return (1);
}

int		quit(t_mlx_data *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (1);
}
