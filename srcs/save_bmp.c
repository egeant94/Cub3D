/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 09:46:39 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 11:40:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int		write_bmp_header(int fd, int filesize, t_mlx_data *mlx)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
	{
		bmpfileheader[i] = (unsigned char)(0);
		i++;
	}
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = mlx->set->s_width;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = mlx->set->s_height;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

int		my_mlx_pixel_reverse_2(t_mlx_data *mlx, int x, int y)
{
	char *color;

	color = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	return (*(int *)color);
}

int		write_bmp_data(int fd, t_mlx_data *mlx, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = mlx->set->s_height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < mlx->set->s_width)
		{
			color = my_mlx_pixel_reverse_2(mlx, j, i);
			if (write(fd, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(fd, &zero, pad) < 0)
				return (0);
			j++;
		}
		i--;
	}
	return (1);
}

int		save_bmp(t_mlx_data *mlx)
{
	int			filesize;
	int			fd;
	int			pad;

	if (frame_render(mlx, mlx->cam, mlx->world_map, 1) == -1)
		return (quit(mlx));
	pad = (4 - ((int)mlx->set->s_width * 3) % 4) % 4;
	filesize = 54 + (3 * ((int)mlx->set->s_width + pad) *
					(int)mlx->set->s_height);
	if ((fd = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, 0777)) == -1)
		return (print_error(strerror(errno)));
	if (!write_bmp_header(fd, filesize, mlx))
		return (print_error("Write failed on screenshot.bmp"));
	if (!write_bmp_data(fd, mlx, pad))
		return (print_error("Write failed on screenshot.bmp"));
	close(fd);
	return (1);
}
