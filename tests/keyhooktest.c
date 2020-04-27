#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include "../libft/libft.h"

typedef struct  s_vars {
    void        *mlx;
    void        *win;
}          		t_vars;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


void			redimg(t_vars vars)
{
	t_data	img;
	int		x;
	int		y;

	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	while (y <= 1080)
	{
		x = 0;
		while (x <= 1920)
		{
			my_mlx_pixel_put(&img, x, y, 0xFFFFFF00);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
}

int             keycode(int keycode, t_vars *vars)
{
	redimg(*vars);
	return (mlx_string_put(vars->mlx, vars->win, 1000, 1000, 0x0000FF00, ft_itoa(keycode)));
}

int             main(void)
{
    t_vars      vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_key_hook(vars.win, keycode, &vars);
    mlx_loop(vars.mlx);
} 