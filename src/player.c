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

	x = -5;
	while (x < 6)
	{
		// mlx_pixel_put(game->mlx, game->win, player->pos.x + x, player->pos.y, MRED);
		game->canvas.data[(int)player->pos.y * WIN_WIDTH + (int)player->pos.x + x] = MRED;
		// mlx_pixel_put(game->mlx, game->win, player->pos.x, player->pos.y + x, MRED);
		game->canvas.data[(int)(player->pos.y + x) * WIN_WIDTH + (int)player->pos.x] = MRED;
		x++;
	}
	mlx_line_put(game, ray_init(player->pos, player->dir), VIEW_DISTANCE, MRED);
	// x = 1;
	angle_step = FOV_ANGLE_HALF / NUM_RAYS;
	// while (x <= NUM_RAYS)
	// {
	// 	dir = vector_rotate(player->dir, x * angle_step);
	// 	mlx_line_put(game, ray_init(player->pos, dir), VIEW_DISTANCE, MRED);
	// 	dir = vector_rotate(player->dir, -x * angle_step);
	// 	mlx_line_put(game, ray_init(player->pos, dir), VIEW_DISTANCE, MRED);
	// 	x++;
	// }
	x = NUM_RAYS;
	dir = vector_rotate(player->dir, x * angle_step);
	mlx_line_put(game, ray_init(player->pos, dir), VIEW_DISTANCE, MRED);
	dir = vector_rotate(player->dir, -x * angle_step);
	mlx_line_put(game, ray_init(player->pos, dir), VIEW_DISTANCE, MRED);
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

	player = &game->player;
	if (keycode == ESC)
		window_exit(game);
	if (keycode == UP)
	{
		player->pos.x += player->dir.x * player->speed;
		player->pos.y += player->dir.y * player->speed;
	}
	if (keycode == DOWN)
	{
		player->pos.x -= player->dir.x * player->speed;
		player->pos.y -= player->dir.y * player->speed;
	}
	if (keycode == LEFT)
	{
		player->pos.x += player->dir.y * player->speed;
		player->pos.y -= player->dir.x * player->speed;
	}
	if (keycode == RIGHT)
	{
		player->pos.x -= player->dir.y * player->speed;
		player->pos.y += player->dir.x * player->speed;
	}
	if (keycode == RIGHT_ARROW)
		player->dir = vector_rotate(player->dir, 0.09);
	if (keycode == LEFT_ARROW)
		player->dir = vector_rotate(player->dir, -0.09);
	game_update(game);
	return (0);
}
