#include "cub3D.h"

// raycasting.c

/*
** 線分の向きを4つに分類する
** 上45度, 右45度, 下45度, 左45度
** line: 線分
** return: 0: 上, 1: 右, 2: 下, 3: 左
*/
int	segment_direction(t_line_segment line)
{
	double	delta_x;
	double	delta_y;

	// if (line.line.inclination == 0)
	// {
	// 	if (line.end.y < line.start.y)
	// 		return (0);
	// 	else
	// 		return (2);
	// }
	delta_x = fabs(line.end.x - line.start.x);
	delta_y = fabs(line.end.y - line.start.y);
	if (delta_y <= delta_x) // 水平の方が長い
	{
		if (line.start.x < line.end.x) // 右向き
			return (1);
		else
			return (3);
	}
	else // 垂直の方が長い
	{
		if (line.end.y < line.start.y) // 上向き
			return (0);
		else
			return (2);
	}
}

/*
** 壁との当たり判定を行う関数
** game: ゲーム構造体
** ray: レイ
** num: レイの番号
** angle: レイの角度
*/
void	check_wall(t_game *game, t_line_segment ray, int num, double angle)
{
	t_wall	wall;

	if (segment_direction(ray) == 0)
		wall = dda_up(game, ray);
	else if (segment_direction(ray) == 1)
		wall = dda_right(game, ray);
	else if (segment_direction(ray) == 2)
		wall = dda_down(game, ray);
	else
		wall = dda_left(game, ray);
	draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall.pos)), wall.color);
}

/*
** レイキャスティング
** プレイヤーの視界に沿ってレイを飛ばし、壁との交点を求める
** game: ゲーム構造体
** player: プレイヤー構造体
*/
void	raycasting(t_game *game, t_player *player)
{
	t_line_segment	ray;
	int			x;
	double		angle_step;
	t_vector	dir;

	angle_step = FOV_ANGLE / NUM_RAYS;
	x = NUM_RAYS / 2;
	while (--x >= 0)
	{
		dir = vector_rotate(player->dir, x * angle_step);
		ray = ray_to_segment(ray_init(player->pos, dir), VIEW_DISTANCE);
		check_wall(game, ray, x, x * angle_step);
	}
	while (x >= -(NUM_RAYS / 2))
	{
		dir = vector_rotate(player->dir, x * angle_step);
		ray = ray_to_segment(ray_init(player->pos, dir), VIEW_DISTANCE);
		check_wall(game, ray, x, x * angle_step);
		x--;
	}
}

/*
** 壁を描画する関数
** game: ゲーム構造体
** num: レイの番号
** angle: レイの角度
** distance: 壁までの距離
*/
void	draw_wall(t_game *game, int num, double angle, double distance, int color)
{
	t_vector	start;
	t_vector	size;
	double		rate;

	rate = 50000 / (distance * cos(angle));
	start = vector_init(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	size = vector_init(1, rate);
	start.x += num;
	draw_rect(game, start, size, color);
}
