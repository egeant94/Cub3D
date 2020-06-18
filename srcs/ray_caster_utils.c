/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:17:56 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 09:44:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		x_inter->x += (-cam->player_dx);
		x_inter->y += cam->player_dx * tan(rad) * cam->tile_step_y;
	}
	y_inter->x = cam->player_x + cam->player_dx;
	y_inter->y = cam->player_y + cam->player_dy;
	if (cam->tile_step_y == 1)
	{
		y_inter->x += (1.0 - cam->player_dy) / tan(rad) * cam->tile_step_x;
		y_inter->y += 1.0 - cam->player_dy;
	}
	else
	{
		y_inter->x += (cam->player_dy) / tan(rad) * cam->tile_step_x;
		y_inter->y += (-cam->player_dy);
	}
}

int		unknown_key(char *line)
{
	if (ft_strlen(line) > 0)
	{
		if (line[0] != '\0' && !(line[0] == 'N' && line[1] == 'O')
			&& !(line[0] == 'S' && line[1] == 'O')
			&& !(line[0] == 'W' && line[1] == 'E')
			&& !(line[0] == 'E' && line[1] == 'A')
			&& !(line[0] == 'S' && line[1] != 'O')
			&& !(line[0] == 'F')
			&& !(line[0] == 'C')
			&& !(line[0] == 'R'))
			return (print_error("Unkown key in config file"));
	}
	return (0);
}

int		check_line(char *line)
{
	int i;

	i = 1;
	while (line[i] != '\0')
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ' && line[i] != ',')
			return (1);
		i++;
	}
	return (0);
}

void	free_tex(t_mlx_data *mlx, t_settings *set)
{
	if (set->north.img != 0)
		mlx_destroy_image(mlx->mlx, set->north.img);
	if (set->south.img != 0)
		mlx_destroy_image(mlx->mlx, set->south.img);
	if (set->west.img != 0)
		mlx_destroy_image(mlx->mlx, set->west.img);
	if (set->east.img != 0)
		mlx_destroy_image(mlx->mlx, set->east.img);
	if (set->sprite.img != 0)
		mlx_destroy_image(mlx->mlx, set->sprite.img);
}

void	finish_file(t_mlx_data *mlx)
{
	int ret;

	ret = get_next_line(mlx->cub_fd, &mlx->line);
	while (ret != 0)
	{
		if (ret == -1)
			return ;
		free_line(&mlx->line);
		ret = get_next_line(mlx->cub_fd, &mlx->line);
	}
	free_line(&mlx->line);
}
