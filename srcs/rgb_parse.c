/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 11:24:09 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 09:44:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			get_texture(t_texture *tex, char *path, t_mlx_data *mlx)
{
	if (tex->img != 0)
		return (1);
	if (split_len(mlx->split) == 1)
	{
		if (mlx->line[0] == 'S' && mlx->line[1] != 'O')
			path = mlx->line + 1;
		else
			path = mlx->line + 2;
	}
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
	if (ft_strlen(line) >= 1 && split_len(mlx->split) >= 1)
	{
		if (line[0] == 'N' && line[1] == 'O')
			if (get_texture(&set->north, mlx->split[1], mlx))
				return (print_error("Problem with the North texture"));
		if (line[0] == 'S' && line[1] == 'O')
			if (get_texture(&set->south, mlx->split[1], mlx))
				return (print_error("Problem with the South texture"));
		if (line[0] == 'W' && line[1] == 'E')
			if (get_texture(&set->west, mlx->split[1], mlx))
				return (print_error("Problem with the West texture"));
		if (line[0] == 'E' && line[1] == 'A')
			if (get_texture(&set->east, mlx->split[1], mlx))
				return (print_error("Problem with the East texture"));
		if (line[0] == 'S' && line[1] != 'O')
			if (get_texture(&set->sprite, mlx->split[1], mlx))
				return (print_error("Problem with the Sprite texture"));
	}
	if (unknown_key(line))
		return (1);
	return (0);
}

void		set_rgb(int *r, int *g, int *b, t_mlx_data *mlx)
{
	int i;

	i = 0;
	*r = ft_custom_atoi(mlx->line + 1);
	while (mlx->line[i] != 0)
	{
		if (mlx->line[i] == ',')
		{
			*g = ft_custom_atoi(mlx->line + i + 1);
			i++;
			break ;
		}
		i++;
	}
	while (mlx->line[i] != 0)
	{
		if (mlx->line[i] == ',')
		{
			*b = ft_custom_atoi(mlx->line + i + 1);
			break ;
		}
		i++;
	}
}

int			double_color(char *line, t_settings *set)
{
	if (line[0] == 'F')
	{
		if (set->floor_c != -1)
			return (print_error("Floor colour is defined multiple times"));
		if (check_line(line))
			return (print_error("Floor color is flawed"));
	}
	if (line[0] == 'C')
	{
		if (set->ceiling_c != -1)
			return (print_error("Ceiling colour is defined multiple times"));
		if (check_line(line))
			return (print_error("Ceiling color is flawed"));
	}
	return (0);
}

int			set_colours(t_settings *set, char *line, t_mlx_data *mlx)
{
	int r;
	int g;
	int b;

	r = -1;
	g = -1;
	b = -1;
	if (double_color(line, set))
		return (1);
	if (ft_strlen(line) >= 1 && split_len(mlx->split) >= 2)
		set_rgb(&r, &g, &b, mlx);
	if (line[0] == 'F')
	{
		if (r < 0 || r > 255 || g < 0 || g > 255 || g < 0 || b < 0 || b > 255)
			return (print_error("Floor colour is badly written"));
		set->floor_c = create_trgb(b, g, r, 0);
		return (0);
	}
	if (line[0] == 'C')
	{
		if (r < 0 || r > 255 || g < 0 || g > 255 || g < 0 || b < 0 || b > 255)
			return (print_error("Ceiling colour is badly written"));
		set->ceiling_c = create_trgb(b, g, r, 0);
	}
	return (0);
}
