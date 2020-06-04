/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:20:36 by user42            #+#    #+#             */
/*   Updated: 2020/06/04 15:09:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

int		**create_map(void)
{
	int			**map;
	int			i;
	int			y;

	map = malloc(sizeof(int *) * (6 + 1));
	map[6] = 0;
	i = 0;
	while (i < 6)
	{
		map[i] = malloc(sizeof(int) * 6);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		y = 0;
		while (y < 6)
		{
			map[i][y] = 0;
			y++;
		}
		i++;
	}
	i = 0;
	while (i < 6)
	{
		map[0][i] = 1;
		map[5][i] = 1;
		map[i][0] = 1;
		map[i][5] = 1;
		i++;
	}
	map[1][2] = 1;
	map[2][3] = 2;
	map[2][2] = 2;
	map[3][2] = 1;
	i = 0;
	y = 0;
	while (i < 6)
	{
		y = 0;
		while (y < 6)
		{
			printf("%d, ", map[i][y]);
			y++;
		}
		printf("\n");
		i++;
	}
	return (map);
}

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

int			print_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(1, "Error\n", 7);
	write(1, str, len);
	write(1, "\n", 1);
	return (1);
}

void		free_map(t_mlx_data *mlx)
{
	int i;

	if (mlx->world_map != 0)
	{
		i = 0;
		while (mlx->world_map[i] != 0)
		{
			free(mlx->world_map[i]);
			i++;
		}
		free(mlx->world_map);
		mlx->world_map = 0;
	}
}

void		free_line(char **str)
{
	if (*str != 0)
	{
		free(*str);
		*str = 0;
	}
}

void		split_free(t_mlx_data *mlx)
{
	int	i;

	i = 0;
	if (mlx->split != 0)
	{
		while(mlx->split[i] != 0)
		{
			free(mlx->split[i]);
			i++;
		}
		free(mlx->split);
		mlx->split = 0;
	}
}

int			split_len(char **tab)
{
	int	i;

	i = 0;
	while(tab[i] != 0)
		i++;
	return (i);
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
			break;
		}
		i++;
	}
	while (mlx->split[1][i] != 0)
	{
		if (mlx->split[1][i] == ',')
		{
			*b = ft_atoi(mlx->split[1] + i + 1);
			break;
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

int			letter_to_number(char c, int *arr, int i)
{
	if (c == ' ')
		arr[i] = -2;
	else if (c == '0')
		arr[i] = 0;
	else if (c == '1')
		arr[i] = 1;
	else if (c == '2')
		arr[i] = 2;
	else if (c == 'N')
		arr[i] = 3;
	else if (c == 'S')
		arr[i] = 4;
	else if (c == 'W')
		arr[i] = 5;
	else if (c == 'E')
		arr[i] = 6;	
	else
	{
		free(arr);
		return (-1);
	}
	return (0);
}

int			*line_to_arr(t_mlx_data *mlx)
{
	int		*arr;
	int		i;

	if ((arr = malloc((ft_strlen(mlx->line) + 1) * sizeof(*arr))) == 0)
	{
		print_error("Malloc failed while parsing the map");
		return (0);
	}
	arr[ft_strlen(mlx->line)] = -1;
	i = 0;
	while (mlx->line[i] != 0)
	{
		if (letter_to_number(mlx->line[i], arr, i))
		{
			print_error("Unknown character in the map");
			return (0);
		}
		i++;
	}
	free_line(&mlx->line);
	return (arr);
}

int			realloc_map(t_mlx_data *mlx, int size)
{
	int		i;
	int		**new_map;

	i = 0;
	while (mlx->world_map[i] != 0)
		i++;
	if ((new_map = malloc((i + size + 1) * sizeof(int *))) == 0)
		return (print_error("Malloc failed while parsing the map"));
	new_map[i + size] = 0;
	i = 0;
	while (mlx->world_map[i] != 0)
	{
		new_map[i] = mlx->world_map[i];
		i++;
	}
	free(mlx->world_map);
	mlx->world_map = new_map;
	return (0);
}

int			new_format(t_mlx_data *mlx, int i, int y)
{
	int	*formated_line;

	i = 0;
	while (mlx->world_map[i] != 0)
	{
		if ((formated_line = malloc((mlx->cam->max_x + 1) * sizeof(int))) == 0)
			return (print_error("Malloc failed while parsing map"));
		formated_line[mlx->cam->max_x] = -1;
		y = 0;
		while (y < mlx->cam->max_x)
		{
			formated_line[y] = -2;
			y++;
		}
		y = 0;
		while (mlx->world_map[i][y] != -1)
		{
			formated_line[y] = mlx->world_map[i][y];
			y++;
		}
		free(mlx->world_map[i]);
		mlx->world_map[i] = formated_line;
		i++;
	}
	i = 0;
	while (mlx->world_map[i] != 0)
	{
		y = 0;
		while (mlx->world_map[i][y] != -1)
		{
			if (mlx->world_map[i][y] == 3)
			{
				mlx->cam->player_x = y;
				mlx->cam->player_y = i;
			}
			if (mlx->world_map[i][y] == -2)
				ft_printf("c");
			else
				ft_printf("%d", mlx->world_map[i][y]);
			y++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("Start : %d %d\n", mlx->cam->player_x, mlx->cam->player_y);
	return (0);
}


int			format_map(t_mlx_data *mlx)
{
	int	i;
	int y;

	i = 0;
	while (mlx->world_map[i] != 0)
	{
		y = 0;
		while (mlx->world_map[i][y] != -1)
			y++;
		if (y > mlx->cam->max_x)
			mlx->cam->max_x = y;
		i++;
	}
	mlx->cam->max_y = i;
	ft_printf("%d, %d\n", mlx->cam->max_x, mlx->cam->max_y);
	if (new_format(mlx, i, y))
		return (1);
	return (0);
}

int			get_map(int ret, t_mlx_data *mlx)
{
	int		i;

	if ((mlx->world_map = malloc(2 * sizeof(*(mlx->world_map)))) == 0)
		return (print_error("Malloc failed while parsing map"));
	if ((mlx->world_map[0] = line_to_arr(mlx)) == 0)
		return (1);
	mlx->world_map[1] = 0;
	ret = get_next_line(mlx->cub_fd, &mlx->line);
	i = 1;
	while (ret != 0)
	{
		if (realloc_map(mlx, 1))
			return (1);
		if ((mlx->world_map[i] = line_to_arr(mlx)) == 0)
			return (1);
		i++;
		ret = get_next_line(mlx->cub_fd, &mlx->line);
	}
	if (format_map(mlx))
		return (1);
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
	// set->floor_c = 0xBBEFDECD;
	// set->ceiling_c = 0x0000CCFF;
	// free_map(mlx);
	// mlx->world_map = create_map();
	// mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, set->s_width,
							set->s_height, "Cub3D");
	// if (get_texture(&set->north, "./textures/grass.xpm", mlx))
	// 	return (print_error("North texture not found"));
	// if (get_texture(&set->south, "./textures/brick.xpm", mlx))
	// 	return (print_error("South texture not found"));
	// if (get_texture(&set->east, "./textures/wood.xpm", mlx))
	// 	return (print_error("East texture not found"));
	// if (get_texture(&set->west, "./textures/metal.xpm", mlx))
	// 	return (print_error("West texture not found"));
	// if (get_texture(&set->sprite, "./textures/sprite.xpm", mlx))
	// 	return (print_error("Sprite texture not found"));
	return (0);
}
