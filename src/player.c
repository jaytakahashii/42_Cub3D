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
	int			x;
	t_vector	dir;
	double		angle_step;

	angle_step = FOV_ANGLE / NUM_RAYS;
	x = -5;
	while (x < 6)
	{
		game->canvas.data[(int)player->pos.y
			* WIN_WIDTH + (int)player->pos.x + x] = MRED;
		game->canvas.data[(int)(player->pos.y + x)
			* WIN_WIDTH + (int)player->pos.x] = MRED;
		x++;
	}
	// ここから下は最後全部消す

	// (void)angle_step;
	// (void)dir;
	// x = 0;
	// while (x < NUM_RAYS / 2)
	// {
	// 	dir = vector_rotate(player->dir, x * angle_step);
	// 	draw_line(game, ray_init(player->pos, dir), VIEW_DISTANCE, MRED);
	// 	if (x == 0)
	// 	{
	// 		x++;
	// 		continue;
	// 	}
	// 	dir = vector_rotate(player->dir, -x * angle_step);
	// 	draw_line(game, ray_init(player->pos, dir), VIEW_DISTANCE, MRED);
	// 	x++;
	// }
	x = NUM_RAYS / 2;
	dir = vector_rotate(player->dir, x * angle_step);
	draw_line(game, ray_init(player->pos, dir), VIEW_DISTANCE, MRED);
	dir = vector_rotate(player->dir, -x * angle_step);
	draw_line(game, ray_init(player->pos, dir), VIEW_DISTANCE, MRED);

	// ここまで
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
	if (game->map_info->map
		[(int)(player->pos.y / TILE_SIZE)]
		[(int)((new.x + margin.x) / TILE_SIZE)] != '1')
		player->pos.x = new.x;
	if (game->map_info->map
		[(int)((new.y + margin.y) / TILE_SIZE)]
		[(int)(player->pos.x / TILE_SIZE)] != '1')
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
// int	key_hook(int keycode, t_game *game)
// {
// 	t_player	*player;

// 	player = &game->player;
// 	if (keycode == ESC)
// 		window_exit(game);
// 	if (keycode == UP)
// 	{
// 		player->pos.x += player->dir.x * player->speed;
// 		player->pos.y += player->dir.y * player->speed;
// 	}
// 	if (keycode == DOWN)
// 	{
// 		player->pos.x -= player->dir.x * player->speed;
// 		player->pos.y -= player->dir.y * player->speed;
// 	}
// 	if (keycode == LEFT)
// 	{
// 		player->pos.x += player->dir.y * player->speed;
// 		player->pos.y -= player->dir.x * player->speed;
// 	}
// 	if (keycode == RIGHT)
// 	{
// 		player->pos.x -= player->dir.y * player->speed;
// 		player->pos.y += player->dir.x * player->speed;
// 	}
// 	if (keycode == RIGHT_ARROW)
// 		player->dir = vector_rotate(player->dir, 0.09);
// 	if (keycode == LEFT_ARROW)
// 		player->dir = vector_rotate(player->dir, -0.09);
// 	game_update(game);
// 	return (0);
// }

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

int		key_press(int keycode, t_game *game)
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

int		key_release(int keycode, t_game *game)
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
