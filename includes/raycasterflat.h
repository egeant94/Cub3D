/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasterflat.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:21:38 by osboxes           #+#    #+#             */
/*   Updated: 2020/05/06 14:54:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTERFLAT_H
# define RAYCASTERFLAT_H
# define MAP_MAX 6
# define FOV 110
# define SPEED_M 1
# define M_PI 3.14159265358979323846
# include <stdlib.h>
# include <stdio.h> //studio.h
# include <mlx.h>
# include "../libft/libft.h"
# include "../printf/includes/ft_printf.h"
# include <math.h>
# include <string.h>

typedef struct	s_coordinates
{
	float x;
	float y;
}				t_coord;

typedef struct	s_camera
{
	int		player_x;
	int		player_y;
	float	player_dx;
	float	player_dy;
	float	h_o_v;
	float	beta_ang;
	float	theta_ang;
	t_coord	x_intercept;
	t_coord	y_intercept;
	float	x_step;
	float	y_step;
	int		tile_step_x;
	int		tile_step_y;
}				t_camera;

typedef struct	s_movements
{
	int		forward;
	int		backward;
	int		left;
	int		right;
	int		cam_left;
	int		cam_right;
}				t_movements;

typedef struct	s_texture
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_texture;

typedef struct	s_settings
{
	int			s_width;
	int			s_height;
	float		wall_height;
	int			floor_c;
	int			ceiling_c;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_texture	sprite;
}				t_settings;

typedef struct	s_mlx_data
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			**world_map;
	t_camera	*cam;
	t_movements	*move;
	t_settings	*set;
}				t_mlx_data;
void			init_camera(t_camera *cam);
void			my_mlx_pixel_put(t_mlx_data *mlx, int x, int y, int color);
void			angle_over_under(float *angle);
float			angle_to_quadrant(float *angle, t_camera *cam);
float			quadrant_to_angle(float *angle, t_camera *cam);
void			first_int(t_camera *cam, float rad,
							t_coord *x_inter, t_coord *y_inter);
void			hit_hor(t_camera *cam, float rad, int **world_map);
void			hit_wall(t_camera *cam, float rad, int **world_map);
float			min_ray_dist(t_camera *cam, int **world_map, float angle);
void			print_vertical_line(t_mlx_data *mlx, int x,
									float dist, t_camera cam);
void			floor_and_ceiling(t_mlx_data *mlx);
void			frame_render(t_mlx_data *mlx, t_camera *cam,
										int **world_map);
void			fix_player_pos(t_camera *cam);
void			change_player_pos(t_camera *cam, int **world_map, t_coord temp);
void			move(t_camera *cam, int **world_map, int dir);
int				key_press(int keycode, t_mlx_data *mlx);
int				key_release(int keycode, t_mlx_data *mlx);
int				renderer(t_mlx_data *mlx);
void			init_movements(t_movements *move);
int				quit(t_mlx_data *mlx);
void			init_settings(t_settings *set, t_mlx_data *mlx);
int				get_texture(t_texture *tex, char *path, t_mlx_data *mlx);
int				my_mlx_pixel_reverse(t_texture *mlx, int x, int y);
#endif
