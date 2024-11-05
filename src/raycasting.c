#include "cub3D.h"

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

	delta_x = fabs(line.end.x - line.start.x);
	delta_y = fabs(line.end.y - line.start.y);
	if (delta_y <= delta_x)
	{
		if (line.start.x < line.end.x)
			return (1);
		else
			return (3);
	}
	else
	{
		if (line.end.y < line.start.y)
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
	wall.distance = vector_len(vector_from_to(ray.start, wall.pos));
	draw_wall(game, wall, num, angle);
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
	int				i;
	double			angle_step;
	t_vector		dir;

	angle_step = FOV_ANGLE / NUM_RAYS;
	i = NUM_RAYS / 2;
	game->y = 0;
	while (i >= -(NUM_RAYS / 2))
	{
		dir = vector_rotate(player->dir, i * angle_step);
		ray = ray_to_segment(ray_init(player->pos, dir), VIEW_DISTANCE);
		check_wall(game, ray, i, i * angle_step);
		i--;
	}
}
