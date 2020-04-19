#include "../includes/raycasterflat.h"
#define screenWidth 1000
#define screenHeight 1000
#define map_max 6
#define FOV 90
#define WALL_HEIGHT 0.5
typedef struct s_camera
{
	int player_x;
	int player_y;
	float player_dx;
	float player_dy;
	float dir_x;
	float dir_y;
	float beta_ang;
	float theta_ang;
	float x_intercept;
	float y_intercept;
	float x_step;
	float y_step;
	int tile_step_x;
	int tile_step_y;
} t_camera;

typedef struct s_mlx_data
{
	void *mlx;
	void *win;
	void *img;
	void *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_mlx_data;

typedef struct s_coordinates
{
	float x;
	float y;
} t_coordinates;

void my_mlx_pixel_put(t_mlx_data *mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	print_vertical_line(t_mlx_data *mlx, int x, float dist)
{
	float		y;
	float		wall;

	y = 0;
	wall = (float)WALL_HEIGHT / dist;
	while (y < screenHeight / 2)
	{
		if ((y / (screenHeight / 2)) < wall)
		{
			my_mlx_pixel_put(mlx, x, screenHeight / 2 + y, 0xFFFFFF00);
			my_mlx_pixel_put(mlx, x, screenHeight / 2 - y, 0xFFFFFF00);
		}
		y++;
	}
}

int	main(void)
{
	t_mlx_data mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "raycasterflat");
	mlx.img = mlx_new_image(mlx.mlx, screenWidth, screenHeight);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel,
								  &mlx.line_length, &mlx.endian);
	int	column = 0;
	float ray_dist = 0.4;
	while (column < screenWidth)
	{
		print_vertical_line(&mlx, column, ray_dist);
		ray_dist += 0.4 / (float)screenWidth;
		printf("%f\n", ray_dist);
		column++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
}