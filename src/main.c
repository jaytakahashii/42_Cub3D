/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:27:21 by kosnakam          #+#    #+#             */
/*   Updated: 2024/11/08 13:34:14 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub_check(char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4))
		error_exit("Must be a .cub file", NULL);
}

void	game_init(t_game *game)
{
	int	x;

	x = -1;
	while (++x < (WIN_WIDTH * (WIN_HEIGHT / 2)))
		game->canvas.data[x] = game->map_info->c;
	while (x < WIN_WIDTH * WIN_HEIGHT)
		game->canvas.data[x++] = game->map_info->f;
	raycasting(game, &game->player);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas.img, 0, 0);
}

void	game_loop(t_game *game)
{
	mlx_hook(game->win, 17, 0, (void *)window_exit, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_loop_hook(game->mlx, key_hook, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop(game->mlx);
}

int	game_update(t_game *game)
{
	int	x;

	x = -1;
	while (++x < (WIN_WIDTH * (WIN_HEIGHT / 2)))
		game->canvas.data[x] = game->map_info->c;
	while (x < WIN_WIDTH * WIN_HEIGHT)
		game->canvas.data[x++] = game->map_info->f;
	x = -1;
	mlx_put_image_to_window(game->mlx, game->win, game->canvas.img, 0, 0);
	raycasting(game, &game->player);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game.alloc = NULL;
	if (argc != 2)
		error_exit("Invalid arguments", NULL);
	cub_check(argv);
	map_scan(&game, argv[1]);
	map_check(&game, (&game)->map_info);
	if (set_img(&game))
		error_exit("Failed to set image", NULL);
	game_init(&game);
	game_loop(&game);
	return (0);
}
