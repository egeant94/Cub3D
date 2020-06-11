/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasterflat.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:21:38 by osboxes           #+#    #+#             */
/*   Updated: 2020/06/11 09:43:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define FOV 110
# define SPEED_M 1
# define M_PI 3.14159265358979323846
# include <stdlib.h>
# include <stdio.h> //studio.h
# include <mlx.h>
# include "../libft/libft.h"
# include "../printf/includes/ft_printf.h"
# include "../minilibx_linux/mlx.h"
# include <math.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

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
	float	wall_offset;
	float	h_o_v;
	float	beta_ang;
	float	theta_ang;
	t_coord	x_intercept;
	t_coord	y_intercept;
	float	x_step;
	float	y_step;
	int		tile_step_x;
	int		tile_step_y;
	float	plan_size;
	float	*dists;
	t_coord	*sprites;
	float	*sprite_dists;
	int		max_x;
	int		max_y;
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
	int			cub_fd;
	char		*line;
	char		**split;
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
int				hit_hor(t_camera *cam, float rad, int **world_map);
int				hit_wall(t_camera *cam, float rad, int **world_map);
float			min_ray_dist(t_camera *cam, int **world_map, float angle);
void			print_vertical_line(t_mlx_data *mlx, int x, float dist);
void			print_vline_2(t_mlx_data *mlx, int x, float dist, float tex_y);
void			floor_and_ceiling(t_mlx_data *mlx);
int				frame_render(t_mlx_data *mlx, t_camera *cam,
										int **world_map);
void			fix_player_pos(t_camera *cam);
void			change_player_pos(t_camera *cam, int **world_map, t_coord temp);
void			move(t_camera *cam, int **world_map, int dir);
int				key_press(int keycode, t_mlx_data *mlx);
int				key_release(int keycode, t_mlx_data *mlx);
int				renderer(t_mlx_data *mlx);
void			init_movements(t_movements *move);
int				quit(t_mlx_data *mlx);
int				init_settings(t_settings *set, t_mlx_data *mlx, int argc,
								char **argv);
int				get_texture(t_texture *tex, char *path, t_mlx_data *mlx);
int				my_mlx_pixel_reverse(t_texture *mlx, int x, int y);
t_texture		*nwse_tex(t_camera cam, t_mlx_data *mlx);
float			wall_offseter(float dist, t_texture *tex,
							float *tex_y, t_mlx_data *mlx);
int				init_y(float wall_offset);
float			inc_tex_y(float w_o, t_texture *tex,
							t_mlx_data *mlx, float dist);
t_coord			ray_sprite(t_camera *cam, int **world_map, float angle);
void			free_all(t_mlx_data *mlx, t_camera *cam);
float			*dist_buffer(t_settings *set);
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
void			init_mlx(t_mlx_data *mlx);
void			free_line(char **str);
void			split_free(t_mlx_data *mlx);
void			free_map(t_mlx_data *mlx);
int				get_map(int ret, t_mlx_data *mlx);
int				*line_to_arr(t_mlx_data *mlx);
int				realloc_map(t_mlx_data *mlx, int size);
int				format_map(t_mlx_data *mlx);
int				new_format(t_mlx_data *mlx, int i, int y);
int				print_error(char *str);
int				letter_to_number(char c, int *arr, int i);
void			number_to_pos(t_camera *cam, int i, int y, int nb);
int				start_position(t_mlx_data *mlx, int i, int y);
int				get_texture(t_texture *tex, char *path, t_mlx_data *mlx);
int				set_textures(t_settings *set, char *line, t_mlx_data *mlx);
void			set_rgb(int *r, int *g, int *b, t_mlx_data *mlx);
int				set_colours(t_settings *set, char *line, t_mlx_data *mlx);
int				split_len(char **tab);
int				line_to_set(t_settings *set, char *line, t_mlx_data *mlx);
int				file_reading(t_settings *set, t_mlx_data *mlx);
int				parse_cub(t_settings *set, t_mlx_data *mlx,
							int argc, char **argv);
float			rad_ang_calc(t_coord hit, t_camera *cam, float dist);
int				add_sprite(t_camera *cam, int x, int y);
int				ray_looper(t_mlx_data *mlx, t_camera *cam,
							float plan_size, int **world_map);
int				display_sprites(t_mlx_data *mlx, t_camera *cam);
void			first_int(t_camera *cam, float rad,
							t_coord *x_inter, t_coord *y_inter);
float			dist_calc(t_coord hit, t_camera *cam);
t_coord			sprite_center(t_coord hit);
void			sprite_sorter(float *sprite_dists, t_camera *cam);
void			print_sprite(t_mlx_data *mlx, float dist,
								int x, t_texture *tex);
float			rad_ang_calc(t_coord hit, t_camera *cam, float dist);
void			print_sprites(t_mlx_data *mlx, t_camera *cam, t_texture *tex);
void			vertical_sprite_line(float dist, float width,
										t_mlx_data *mlx, int x);
void			init_set(t_settings *set);
int				mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
int				check_map(t_mlx_data *mlx);
#endif
