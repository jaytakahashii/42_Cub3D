#include "cub3D.h"

// player.c

/*
** プレイヤーの初期化
** x, y: プレイヤーの初期位置
** angle: プレイヤーの初期角度
** speed: プレイヤーの移動速度
*/
t_player	player_init(double x, double y, double angle, double speed)
{
	t_player	ret;

	ret.pos.x = x;
	ret.pos.y = y;
	ret.dir = vector_from_angle(angle);
	ret.angle = angle;
	ret.speed = speed;
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
	int			x;
	t_vector	dir;
	double		angle_step;

	angle_step = FOV_ANGLE / NUM_RAYS; // 視野角をレイの数で分割
	x = -5;
	while (x < 6)
	{
		game->canvas.data[(int)player->pos.y * WIN_WIDTH + (int)player->pos.x + x] = MRED;
		game->canvas.data[(int)(player->pos.y + x) * WIN_WIDTH + (int)player->pos.x] = MRED;
		x++;
	}
	x = NUM_RAYS / 2;
	dir = vector_rotate(player->dir, x * angle_step);
	mlx_line_put(game, ray_init(player->pos, dir), VIEW_DISTANCE, MRED);
	dir = vector_rotate(player->dir, -x * angle_step);
	mlx_line_put(game, ray_init(player->pos, dir), VIEW_DISTANCE, MRED);
}

/*
** プレイヤーと壁の衝突判定
** game: ゲーム構造体
** delta: プレイヤーの移動量
*/
void	player_collision(t_game *game, t_vector delta)
{
	t_player	*player;
	t_vector	new_pos;

	player = &game->player;
	new_pos = vector_add(player->pos, delta);
	if (game->map_info->map[(int)(new_pos.y / TILE_SIZE)][(int)(new_pos.x / TILE_SIZE)] == '1')
		return ;
	player->pos = new_pos;
}

/*
** プレイヤーを動かす関数
** UP: プレイヤーを前進させる
** DOWN: プレイヤーを後退させる
** LEFT: プレイヤーを左に移動させる
** RIGHT: プレイヤーを右に移動させる
** UP_ARROW: プレイヤーを右に回転させる
** DOWN_ARROW: プレイヤーを左に回転させる
** player: プレイヤー構造体
** keycode: キーコード
*/
int	key_hook(int keycode, t_game *game)
{
	t_player	*player;
	t_vector	delta;

	player = &game->player;
	if (keycode == ESC)
		window_exit(game);
	if (keycode == UP)
		delta = vector_mul(player->dir, player->speed);
	if (keycode == DOWN)
		delta = vector_mul(player->dir, -player->speed);
	if (keycode == LEFT)
	{
		delta.x = player->dir.y * player->speed;
		delta.y = -player->dir.x * player->speed;
	}
	if (keycode == RIGHT)
	{
		delta.x = -player->dir.y * player->speed;
		delta.y = player->dir.x * player->speed;
	}
	if (keycode == RIGHT_ARROW)
		player->dir = vector_rotate(player->dir, 0.09);
	if (keycode == LEFT_ARROW)
		player->dir = vector_rotate(player->dir, -0.09);
	player_collision(game, delta);
	game_update(game);
	return (0);
}
