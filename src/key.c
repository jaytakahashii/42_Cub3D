/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:40:01 by jtakahas          #+#    #+#             */
/*   Updated: 2024/12/11 13:40:02 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		window_exit(game);
	else if (keycode == UP)
		game->player.up = 1;
	else if (keycode == DOWN)
		game->player.back = 1;
	else if (keycode == LEFT)
		game->player.left = 1;
	else if (keycode == RIGHT)
		game->player.right = 1;
	else if (keycode == RIGHT_ARROW)
		game->player.turn_right = 1;
	else if (keycode == LEFT_ARROW)
		game->player.turn_left = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == UP)
		game->player.up = 0;
	else if (keycode == DOWN)
		game->player.back = 0;
	else if (keycode == LEFT)
		game->player.left = 0;
	else if (keycode == RIGHT)
		game->player.right = 0;
	else if (keycode == RIGHT_ARROW)
		game->player.turn_right = 0;
	else if (keycode == LEFT_ARROW)
		game->player.turn_left = 0;
	return (0);
}
