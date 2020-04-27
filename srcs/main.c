/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:18:23 by osboxes           #+#    #+#             */
/*   Updated: 2020/04/27 22:52:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

int		**create_map(void)
{
	int			**map;
	int			i;
	int			y;

	map = malloc(sizeof(int *) * 6);
	i = 0;
	while (i < 6)
	{
		map[i] = malloc(sizeof(int) * 6);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		y = 0;
		while (y < 6)
		{
			map[i][y] = 0;
			y++;
		}
		i++;
	}
	i = 0;
	while (i < 6)
	{
		map[0][i] = 1;
		map[5][i] = 1;
		map[i][0] = 1;
		map[i][5] = 1;
		i++;
	}
	map[2][2] = 1;
	i = 0;
	y = 0;
	while (i < 6)
	{
		y = 0;
		while (y < 6)
		{
			printf("%d, ", map[i][y]);
			y++;
		}
		printf("\n");
		i++;
	}
	return (map);
}

int		main(void)
{
	t_camera	cam;
	t_mlx_data	mlx;

	mlx.world_map = create_map();
	init_camera(&cam);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, SCREEN_WIDTH,
							SCREEN_HEIGHT, "raycasterflat");
	calculate_first_frame(&mlx, &cam, mlx.world_map);
	mlx.cam = &cam;
	mlx_hook(mlx.win, 2, 1L << 0, camera, &mlx);
	mlx_loop(mlx.mlx);
}
