/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:40:22 by jtakahas          #+#    #+#             */
/*   Updated: 2024/12/11 13:40:23 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** プレイヤーの初期化
** x, y: プレイヤーの初期位置
** angle: プレイヤーの初期角度
** speed: プレイヤーの移動速度
*/
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

/*
** プレイヤーを描画する関数
** 半径5の円を描画
** プレイヤーの視界は3radianごとに線を引く (60度)
** プレイヤーの向きは赤い線で表示
** game: ゲーム構造体
** player: プレイヤー構造体
*/
void	draw_player(t_game *game, t_player *player)
{
	int		x;

	x = -5;
	while (x < 6)
	{
		game->canvas.data[(int)player->pos.y
			* WIN_WIDTH + (int)player->pos.x + x] = MRED;
		game->canvas.data[(int)(player->pos.y + x)
			* WIN_WIDTH + (int)player->pos.x] = MRED;
		x++;
	}
}

/*
** プレイヤーと壁の衝突判定
** game: ゲーム構造体
** delta: プレイヤーの移動量
*/
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
