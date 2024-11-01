#include "cub3D.h"

/*
** 壁を描画する関数
** game: ゲーム構造体
** num: レイの番号
** angle: レイの角度
** distance: 壁までの距離
*/
void	draw_wall(t_game *game, int num, double angle, double distance, int y)
{
	t_vector	start;
	t_vector		rate;

	rate.y = 10000 / (distance * cos(angle));
	start = vector_init(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	start.x += num;
	draw_rect(game, start, rate, MBLUE, y);
}

// raycasting.c

void	check_wall(t_game *game, t_line_segment ray, int num, double angle, int y)
{
	t_line_segment	segment_1;
	t_line_segment	segment_2;
	t_line_segment	segment_3;
	t_vector		intersection;

	segment_1 = line_segment_init(vector_init(300, 0), vector_init(300, 300));
	segment_2 = line_segment_init(vector_init(0, 300), vector_init(300, 300));
	segment_3 = line_segment_init(vector_init(300, 0), vector_init(0, 300));
	intersection = line_intersection(ray, segment_1);
	if (intersection.x != -1 && intersection.y != -1)
	{
		// draw_circle(game, intersection, 3, MWHITE);
		draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, intersection)), y);
	}
	intersection = line_intersection(ray, segment_2);
	if (intersection.x != -1 && intersection.y != -1)
	{
		// draw_circle(game, intersection, 3, MWHITE);
		draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, intersection)), y);
	}
	intersection = line_intersection(ray, segment_3);
	if (intersection.x != -1 && intersection.y != -1)
	{
		// draw_circle(game, intersection, 3, MWHITE);
		draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, intersection)), y);
	}
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
	double			angle_step;
	t_vector		dir;
	int				x;

	x = 1;
	int y = 0;
	angle_step = FOV_ANGLE_HALF / NUM_RAYS;
	ray = ray_to_segment(ray_init(player->pos, player->dir), VIEW_DISTANCE);
	check_wall(game, ray, 0, 0, y);
	while (x <= NUM_RAYS)
	{
		if (y == TILE_SIZE)
			y = 0;
		dir = vector_rotate(player->dir, x * angle_step);
		ray = ray_to_segment(ray_init(player->pos, dir), VIEW_DISTANCE);
		check_wall(game, ray, x, x * angle_step, y);
		dir = vector_rotate(player->dir, -x * angle_step);
		ray = ray_to_segment(ray_init(player->pos, dir), VIEW_DISTANCE);
		check_wall(game, ray, x * -1, x * -angle_step, y);
		x++;
		y++;
	}
}
