/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:03:53 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 09:43:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int		display_sprites(t_mlx_data *mlx, t_camera *cam)
{
	int i;

	i = 0;
	(void)mlx;
	while (cam->sprites != 0 && cam->sprites[i].x != -1)
		i++;
	if ((cam->sprite_dists = malloc((i + 1) * sizeof(float))) == 0)
		return (-1);
	cam->sprite_dists[i] = -1;
	i = 0;
	while (cam->sprites != 0 && cam->sprites[i].x != -1)
	{
		cam->sprite_dists[i] = dist_calc(sprite_center(cam->sprites[i]), cam);
		i++;
	}
	sprite_sorter(cam->sprite_dists, cam);
	print_sprites(mlx, cam, &mlx->set->sprite);
	return (0);
}

float	dist_calc(t_coord hit, t_camera *cam)
{
	float	dist;
	float	rad_ang;
	float	rad_beta;

	rad_beta = cam->beta_ang / 180 * M_PI;
	dist = sqrt(pow(hit.x - (cam->player_x + cam->player_dx), 2) +
			pow(hit.y - (cam->player_y + cam->player_dy), 2));
	rad_ang = acos(fabs((cam->player_x + cam->player_dx) - hit.x) / dist);
	if (cam->player_x + cam->player_dx > hit.x
		&& cam->player_y + cam->player_dy > hit.y)
		rad_ang = M_PI - (rad_ang + rad_beta);
	else if (cam->player_x + cam->player_dx > hit.x
		&& cam->player_y + cam->player_dy < hit.y)
		rad_ang = M_PI - rad_beta + rad_ang;
	else if (cam->player_x + cam->player_dx < hit.x
			&& cam->player_y + cam->player_dy < hit.y)
		rad_ang = 2 * M_PI - (rad_beta + rad_ang);
	else
		rad_ang = rad_beta - rad_ang;
	dist = fabs(dist * cos(rad_ang));
	return (dist);
}

void	print_sprites(t_mlx_data *mlx, t_camera *cam, t_texture *tex)
{
	int		i;
	int		pixel;
	float	rad_ang;
	float	test;

	i = 0;
	while (cam->sprite_dists[i] != -1)
	{
		rad_ang = cam->beta_ang;
		rad_ang = angle_to_quadrant(&rad_ang, cam);
		rad_ang = rad_ang_calc(
					sprite_center(cam->sprites[i]), cam, cam->sprite_dists[i]);
		pixel = 2;
		test = (tan(rad_ang) + cam->plan_size) / (cam->plan_size * 2);
		pixel = test * mlx->set->s_width;
		print_sprite(mlx, cam->sprite_dists[i], pixel, tex);
		i++;
	}
}

void	print_sprite(t_mlx_data *mlx, float dist, int x, t_texture *tex)
{
	float		width;
	int			hor;

	(void)tex;
	width = (float)mlx->set->s_width / (dist * mlx->set->s_width * 2.87);
	hor = x - (width * mlx->set->s_width / 2);
	while (1)
	{
		if (hor >= x + (width * mlx->set->s_width / 2))
			return ;
		if (hor > 0 && hor < mlx->set->s_width && dist < mlx->cam->dists[hor])
			vertical_sprite_line(dist,
								(hor - x + (width * mlx->set->s_width / 2))
								/ (width * mlx->set->s_width), mlx, hor);
		hor++;
	}
}

void	vertical_sprite_line(float dist, float width, t_mlx_data *mlx, int x)
{
	float		y;
	float		wall_offset;
	float		tex_y;
	int			color;

	wall_offset = wall_offseter(dist, &mlx->set->sprite, &tex_y, mlx);
	y = init_y(wall_offset);
	while (y < mlx->set->s_height && y < mlx->set->s_height - wall_offset)
	{
		tex_y += inc_tex_y(wall_offset, &mlx->set->sprite, mlx, dist);
		color = my_mlx_pixel_reverse(&mlx->set->sprite,
								width * mlx->set->sprite.width, (int)tex_y);
		if (get_t(color) != 0)
			my_mlx_pixel_put(mlx, x, y, color);
		y++;
	}
}
