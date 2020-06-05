/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:18:23 by osboxes           #+#    #+#             */
/*   Updated: 2020/06/05 11:36:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

int		check_second_arg(int argc, char **argv)
{
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7) != 0)
		{
			write(1, "Error\nSecond argument isn't valid\n", 35);
			return (1);
		}
	}
	return (0);
}

int		check_args(int argc, char **argv)
{
	int len;

	if (argc <= 1)
	{
		write(1, "Error\nPlease add a config file .cub as an argument\n", 52);
		return (1);
	}
	if (argc > 3)
	{
		write(1, "Error\nToo many arguments\n", 26);
		return (1);
	}
	if (((len = ft_strlen(argv[1])) < 5)
			|| ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
	{
		write(1, "Error\nConfig file extension isn't .cub\n", 40);
		return (1);
	}
	return (check_second_arg(argc, argv));
}

int		main(int argc, char **argv)
{
	t_camera	cam;
	t_mlx_data	mlx;
	t_movements	move;
	t_settings	set;

	if (check_args(argc, argv))
		return (0);
	init_mlx(&mlx);
	init_camera(&cam);
	init_movements(&move);
	mlx.cam = &cam;
	mlx.move = &move;
	if (init_settings(&set, &mlx, argc, argv))
	{
		quit(&mlx);
		return (0);
	}
	mlx.set = &set;
	mlx_hook(mlx.win, 17, 1L << 17, quit, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);
	mlx_loop_hook(mlx.mlx, renderer, &mlx);
	mlx_loop(mlx.mlx);
}
