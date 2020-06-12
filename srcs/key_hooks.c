/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:15:10 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 10:25:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
**119 = w, 122 = z, 97 = a, 113 = q, 115 = s,
** 100 = d, 65361 = left arrow, 65363 = right arrow
*/

void	free_all(t_mlx_data *mlx, t_camera *cam)
{
	if (mlx->img != 0 && mlx->mlx != 0)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx->img = 0;
	}
	if (cam->dists != 0)
	{
		free(cam->dists);
		cam->dists = 0;
	}
	if (cam->sprites != 0)
	{
		free(cam->sprites);
		cam->sprites = 0;
	}
	if (cam->sprite_dists != 0)
	{
		free(cam->sprite_dists);
		cam->sprite_dists = 0;
	}
	free_line(&mlx->line);
	split_free(mlx);
}

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
	if (frame_render(mlx, mlx->cam, mlx->world_map, 0) == -1)
		return (quit(mlx));
	return (1);
}

int		quit(t_mlx_data *mlx)
{
	free_all(mlx, mlx->cam);
	close(mlx->cub_fd);
	free_map(mlx);
	if (mlx->mlx != 0 && mlx->win != 0)
		mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (1);
}
