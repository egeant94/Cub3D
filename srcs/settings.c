/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:20:36 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 11:24:29 by user42           ###   ########.fr       */
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
	while(tab[i] != 0)
		i++;
	return (i);
}

int			line_to_set(t_settings *set, char *line, t_mlx_data *mlx)
{
	if ((mlx->split = ft_split(line, ' ')) == 0)
		return (print_error("Malloc failed while parsing .cub"));
	if (ft_strlen(line) > 0)
	{
		if (line[0] == 'R')
		{
			if (split_len(mlx->split) < 3)
				return (print_error("Resolution lacks a parameter."));
			set->s_width = ft_atoi(mlx->split[1]);
			set->s_height = ft_atoi(mlx->split[2]);
			if (set->s_width <= 1 || set->s_height <= 0)
				return (print_error("Resolution is too small."));
		}
		if (set_textures(set, line, mlx))
			return (1);
		if (set_colours(set, line, mlx))
			return (1);
	}
	split_free(mlx);
	return (0);
}

int			file_reading(t_settings *set, t_mlx_data *mlx)
{
	int ret;

	ret = get_next_line(mlx->cub_fd, &mlx->line);
	while (ret != 0)
	{
		if (ret == -1)
			return (print_error("Malloc failed while parsing .cub"));
		if (ft_isdigit(mlx->line[0]) || mlx->line[0] == ' ' || mlx->line[0] == '\t')
			break;
		if (line_to_set(set, mlx->line, mlx))
			return (1);
		free_line(&mlx->line);
		ret = get_next_line(mlx->cub_fd, &mlx->line);
	}
	if (ret != 0)
	{
		if (get_map(ret, mlx))
			return (1);
	}
	return (0);
}

int			parse_cub(t_settings *set, t_mlx_data *mlx, int argc, char **argv)
{
	if ((mlx->cub_fd = open(argv[1], O_RDONLY)) == -1)
		return (print_error(strerror(errno)));
	if (file_reading(set, mlx))
		return (1);
	if (argc > 2)
	{
		ft_printf("Saving first image\n");
		return (1);
	}
	return (0);
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

int			init_settings(t_settings *set, t_mlx_data *mlx, int argc,
							char **argv)
{
	if (parse_cub(set, mlx, argc, argv))
		return (1);
	set->wall_height = (float)set->s_width / (float)set->s_height / 3.0;
	mlx->win = mlx_new_window(mlx->mlx, set->s_width,
							set->s_height, "Cub3D");
	return (0);
}
