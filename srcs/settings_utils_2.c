/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 12:17:07 by user42            #+#    #+#             */
/*   Updated: 2020/06/18 12:29:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_custom_atoi(char *str)
{
	int i;
	int result;
	int signe;

	if (str == 0)
		return (0);
	i = 0;
	signe = 1;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		&& str[i] != '\0')
		i++;
	if (str[i] == ',' || str[i] == '\0')
		return (-1);
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = str[i] - '0' + result * 10;
		i++;
	}
	return (result * signe);
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
