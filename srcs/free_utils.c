/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 11:21:28 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 09:44:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		while (mlx->split[i] != 0)
		{
			free(mlx->split[i]);
			i++;
		}
		free(mlx->split);
		mlx->split = 0;
	}
}
