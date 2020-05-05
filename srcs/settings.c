/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:20:36 by user42            #+#    #+#             */
/*   Updated: 2020/05/05 14:08:12 by user42           ###   ########.fr       */
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
		return 1;
	}
	else
		return -1;
}

void		init_settings(t_settings *set, t_mlx_data *mlx)
{
	set->s_width = 1920;
	set->s_height = 1080;
	set->floor_c = 0xBBEFDECD;
	set->ceiling_c = 0x0000CCFF;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, set->s_width,
							set->s_height, "raycasterflat");
	get_texture(&set->north, "./textures/dontusethisone.xpm", mlx);
	get_texture(&set->south, "./textures/dontusethisone.xpm", mlx);
	get_texture(&set->west, "./textures/grass.xpm", mlx);
	get_texture(&set->east, "./textures/grass.xpm", mlx);
}
