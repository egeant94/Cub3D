/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:15:10 by user42            #+#    #+#             */
/*   Updated: 2020/05/01 11:17:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

/*
**119 = w, 122 = z, 97 = a, 113 = q, 115 = s,
** 100 = d, 65361 = left arrow, 65363 = right arrow
*/

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
