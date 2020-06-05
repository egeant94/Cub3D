/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 11:31:17 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 11:56:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

int			print_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(1, "Error\n", 7);
	write(1, str, len);
	write(1, "\n", 1);
	return (1);
}

int			split_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

void		init_mlx(t_mlx_data *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = 0;
	mlx->img = 0;
	mlx->bits_per_pixel = 0;
	mlx->line_length = 0;
	mlx->endian = 0;
	mlx->world_map = 0;
	mlx->cub_fd = 0;
	mlx->line = 0;
	mlx->split = 0;
	mlx->world_map = 0;
}

void		init_camera(t_camera *cam)
{
	cam->player_x = -1;
	cam->player_y = -1;
	cam->player_dx = 0.51;
	cam->player_dy = 0.51;
	cam->h_o_v = 0;
	cam->wall_offset = 0;
	cam->beta_ang = 0;
	cam->theta_ang = 0;
	cam->x_intercept.x = 0;
	cam->x_intercept.y = 0;
	cam->y_intercept.x = 0;
	cam->y_intercept.y = 0;
	cam->x_step = 0;
	cam->y_step = 0;
	cam->tile_step_x = 0;
	cam->tile_step_y = 0;
	cam->sprites = 0;
	cam->sprite_dists = 0;
	cam->dists = 0;
	cam->max_x = 0;
	cam->max_y = 0;
}
