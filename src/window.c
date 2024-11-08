/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:32:24 by kosnakam          #+#    #+#             */
/*   Updated: 2024/11/08 13:32:26 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	game->canvas.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->canvas.data = (int *)mlx_get_data_addr(game->canvas.img,
			&game->canvas.bpp, &game->canvas.size_line, &game->canvas.endian);
}

int	window_exit(t_game *game)
{
	free_allocations(&(game->alloc));
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

bool	out_of_window(t_vector pos)
{
	if (pos.x < 0 || pos.x >= WIN_WIDTH || pos.y < 0 || pos.y >= WIN_HEIGHT)
		return (true);
	return (false);
}
