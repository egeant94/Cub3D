/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 11:24:09 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 11:27:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

int			get_texture(t_texture *tex, char *path, t_mlx_data *mlx)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx, path, &tex->width, &tex->height);
	if (tex->img != 0)
	{
		tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
								&tex->line_length, &tex->endian);
		return (0);
	}
	else
		return (1);
}

int			set_textures(t_settings *set, char *line, t_mlx_data *mlx)
{
	if (ft_strlen(line) >= 2 && split_len(mlx->split) >= 2)
	{
		if (line[0] == 'N' && line[1] == 'O')
			if (get_texture(&set->north, mlx->split[1], mlx))
				return (print_error("North texture not found"));
		if (line[0] == 'S' && line[1] == 'O')
			if (get_texture(&set->south, mlx->split[1], mlx))
				return (print_error("South texture not found"));
		if (line[0] == 'W' && line[1] == 'E')
			if (get_texture(&set->west, mlx->split[1], mlx))
				return (print_error("West texture not found"));
		if (line[0] == 'E' && line[1] == 'A')
			if (get_texture(&set->east, mlx->split[1], mlx))
				return (print_error("East texture not found"));
	}
	if (ft_strlen(line) >= 1 && split_len(mlx->split) >= 2)
		if (line[0] == 'S' && line[1] != 'O')
			if (get_texture(&set->sprite, mlx->split[1], mlx))
				return (print_error("Sprite texture not found"));
	return (0);
}

void		set_rgb(int *r, int *g, int *b, t_mlx_data *mlx)
{
	int i;

	i = 0;
	*r = ft_atoi(mlx->split[1]);
	while (mlx->split[1][i] != 0)
	{
		if (mlx->split[1][i] == ',')
		{
			*g = ft_atoi(mlx->split[1] + i + 1);
			i++;
			break ;
		}
		i++;
	}
	while (mlx->split[1][i] != 0)
	{
		if (mlx->split[1][i] == ',')
		{
			*b = ft_atoi(mlx->split[1] + i + 1);
			break ;
		}
		i++;
	}
}

int			set_colours(t_settings *set, char *line, t_mlx_data *mlx)
{
	int r;
	int g;
	int b;

	r = -1;
	g = -1;
	b = -1;
	if (ft_strlen(line) >= 1 && split_len(mlx->split) >= 2)
		set_rgb(&r, &g, &b, mlx);
	if (line[0] == 'F')
	{
		if (r == -1 || g == -1 || b == -1)
			return (print_error("Floor colour is badly written."));
		set->floor_c = create_trgb(b, g, r, 0);
	}
	if (line[0] == 'C')
	{
		if (r == -1 || g == -1 || b == -1)
			return (print_error("Ceiling colour is badly written."));
		set->ceiling_c = create_trgb(b, g, r, 0);
	}
	return (0);
}