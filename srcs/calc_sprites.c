/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:04:43 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 09:43:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	rad_ang_calc(t_coord hit, t_camera *cam, float dist)
{
	float	rad_ang;

	dist = sqrt(pow(hit.x - (cam->player_x + cam->player_dx), 2) +
			pow(hit.y - (cam->player_y + cam->player_dy), 2));
	rad_ang = acos(fabs((cam->player_x + cam->player_dx) - hit.x) / dist);
	if (cam->player_x + cam->player_dx > hit.x
		&& cam->player_y + cam->player_dy > hit.y)
		rad_ang = M_PI - rad_ang;
	else if (cam->player_x + cam->player_dx > hit.x
		&& cam->player_y + cam->player_dy < hit.y)
		rad_ang = rad_ang + M_PI;
	else if (cam->player_x + cam->player_dx < hit.x
			&& cam->player_y + cam->player_dy < hit.y)
		rad_ang = 2 * M_PI - rad_ang;
	rad_ang = rad_ang * 180 / M_PI;
	rad_ang = cam->beta_ang - rad_ang;
	return (rad_ang / 180 * M_PI);
}

t_coord	sprite_center(t_coord hit)
{
	t_coord center;

	center.x = hit.x + 0.5;
	center.y = hit.y + 0.5;
	return (center);
}

int		add_sprite(t_camera *cam, int x, int y)
{
	t_coord		*new_sprites;
	int			i;
	int			q;

	i = 0;
	while (cam->sprites != 0 && cam->sprites[i].x != -1)
	{
		if (x == cam->sprites[i].x && y == cam->sprites[i].y)
			return (0);
		i++;
	}
	if ((new_sprites = malloc((i + 2) * sizeof(*new_sprites))) == 0)
		return (-1);
	q = 0;
	while (q < i)
	{
		new_sprites[q] = cam->sprites[q];
		q++;
	}
	new_sprites[q].x = x;
	new_sprites[q].y = y;
	new_sprites[q + 1].x = -1;
	free(cam->sprites);
	cam->sprites = new_sprites;
	return (0);
}

float	*dist_buffer(t_settings *set)
{
	float	*buffer;

	buffer = malloc((set->s_width + 1) * sizeof(float));
	buffer[set->s_width] = -1;
	return (buffer);
}

void	sprite_sorter(float *sprite_dists, t_camera *cam)
{
	float	temp;
	t_coord	temp_coord;
	int		i;

	i = 0;
	while (sprite_dists != 0 && sprite_dists[i] != -1)
		i++;
	if (i <= 1)
		return ;
	i = 1;
	while (sprite_dists[i] != -1)
	{
		if (sprite_dists[i] > sprite_dists[i - 1])
		{
			temp = sprite_dists[i];
			temp_coord = cam->sprites[i];
			sprite_dists[i] = sprite_dists[i - 1];
			cam->sprites[i] = cam->sprites[i - 1];
			cam->sprites[i - 1] = temp_coord;
			sprite_dists[i - 1] = temp;
			i = 1;
		}
		i++;
	}
}
