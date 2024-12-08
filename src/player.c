/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:30:19 by kosnakam          #+#    #+#             */
/*   Updated: 2024/12/08 22:11:15 by jay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_player	player_init(double x, double y, double angle)
{
	t_player	ret;

	ret.pos.x = x;
	ret.pos.y = y;
	ret.dir = vector_from_angle(angle);
	ret.angle = angle;
	ret.speed = MOVE_SPEED;
	ret.up = 0;
	ret.back = 0;
	ret.left = 0;
	ret.right = 0;
	ret.turn_left = 0;
	ret.turn_right = 0;
	return (ret);
}

static void	player_collision(t_game *game, t_player *player, t_vector delta)
{
	t_vector	new;
	t_vector	margin;

	new.x = player->pos.x + delta.x;
	new.y = player->pos.y + delta.y;
	if (delta.x > 0)
		margin.x = 10;
	else
		margin.x = -10;
	if (delta.y > 0)
		margin.y = 10;
	else
		margin.y = -10;
	if (game->map_info->map[(int)(player->pos.y / TEXTURE_SIZE)][(int)((new.x
				+ margin.x) / TEXTURE_SIZE)] != '1')
		player->pos.x = new.x;
	if (game->map_info->map[(int)((new.y + margin.y)
			/ TEXTURE_SIZE)][(int)(player->pos.x / TEXTURE_SIZE)] != '1')
		player->pos.y = new.y;
}

static bool	move_player(t_player *player, t_vector *delta)
{
	bool (move) = false;
	int (rotate) = 0;
	if (player->up)
		*delta = vector_mul(player->dir, player->speed);
	if (player->back)
		*delta = vector_mul(player->dir, -player->speed);
	if (player->left)
	{
		delta->x = player->dir.y * player->speed;
		delta->y = -player->dir.x * player->speed;
	}
	if (player->right)
	{
		delta->x = -player->dir.y * player->speed;
		delta->y = player->dir.x * player->speed;
	}
	if (player->turn_right)
		rotate = 1;
	if (player->turn_left)
		rotate = -1;
	player->dir = vector_rotate(player->dir, rotate * ROTATE_SPEED);
	if (delta->x != 0 || delta->y != 0 || rotate != 0)
		move = true;
	return (move);
}

int	key_hook(t_game *game)
{
	t_vector	delta;

	delta = vector_init(0, 0);
	if (move_player(&game->player, &delta))
	{
		player_collision(game, &game->player, delta);
		game_update(game);
	}
	return (0);
}
