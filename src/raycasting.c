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

	if (line.line.inclination == 0)
	{
		if (line.end.y < line.start.y)
			return (0);
		else
			return (2);
	}
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
** DDAアルゴリズム 上向き
** レイと壁の交点を求める
** game: ゲーム構造体
** ray: レイ
** num: レイの番号
** angle: レイの角度
*/
void	dda_0(t_game *game, t_line_segment ray, int num, double angle)
{
	int			map_y;
	double		x;
	t_vector	wall;

	map_y = (int)(ray.start.y / TILE_SIZE);
	while (1)
	{
		x = (line_calc_x(ray.line, map_y * TILE_SIZE) / TILE_SIZE);
		if (game->map_info->map[map_y][(int)x] == '1')
		{
			if (ray.start.x < ray.end.x) // 西の壁
			{
				wall.x = (int)x * TILE_SIZE;
				wall.y = line_calc_y(ray.line, wall.x);
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), WALL_WEST);
			}
			else // 東の壁
			{
				wall.x = ((int)x + 1) * TILE_SIZE;
				wall.y = line_calc_y(ray.line, wall.x);
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), WALL_EAST);
			}
			return;
		}
		if (game->map_info->map[map_y - 1][(int)x] == '1') // 南の壁
		{
			wall.y = map_y * TILE_SIZE;
			wall.x = line_calc_x(ray.line, wall.y);
			draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), WALL_SOUTH);
			return;
		}
		map_y--;
	}
}

/*
** DDAアルゴリズム 右向き
** レイと壁の交点を求める
** game: ゲーム構造体
** ray: レイ
** num: レイの番号
** angle: レイの角度
*/
void	dda_1(t_game *game, t_line_segment ray, int num, double angle)
{
	int			map_x;
	double		y;
	t_vector	wall;

	map_x = (int)(ray.start.x / TILE_SIZE) + 1;
	while (1)
	{
		y = line_calc_y(ray.line, map_x * TILE_SIZE) / TILE_SIZE;
		if (game->map_info->map[(int)y][map_x - 1] == '1')
		{
			if (ray.start.y < ray.end.y) // 北の壁
			{
				wall.y = (int)y * TILE_SIZE;
				wall.x = line_calc_x(ray.line, wall.y);
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), WALL_NORTH);
			}
			else // 南の壁
			{
				wall.y = ((int)y + 1) * TILE_SIZE;
				wall.x = line_calc_x(ray.line, wall.y);
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), WALL_SOUTH);
			}
			return;
		}
		if (game->map_info->map[(int)y][map_x] == '1') // 西の壁
		{
			wall.x = (map_x) * TILE_SIZE;
			wall.y = line_calc_y(ray.line, wall.x);
			draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), WALL_WEST);
			return;
		}
		map_x++;
	}
}

/*
** DDAアルゴリズム 下向き
** レイと壁の交点を求める
** game: ゲーム構造体
** ray: レイ
** num: レイの番号
** angle: レイの角度
*/
void	dda_2(t_game *game, t_line_segment ray, int num, double angle)
{
	int			map_y;
	double		x;
	t_vector	wall;

	map_y = (int)(ray.start.y / TILE_SIZE);
	while (1)
	{
		x = line_calc_x(ray.line, (map_y + 1) * TILE_SIZE) / TILE_SIZE;
		if (game->map_info->map[map_y][(int)x] == '1')
		{
			if (ray.start.x < ray.end.x) // 西の壁
			{
				wall.x = (int)x * TILE_SIZE;
				wall.y = line_calc_y(ray.line, wall.x);
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), WALL_WEST);
			}
			else // 東の壁
			{
				wall.x = ((int)x + 1) * TILE_SIZE;
				wall.y = line_calc_y(ray.line, wall.x);
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), WALL_EAST);
			}
			return;
		}
		if (game->map_info->map[map_y + 1][(int)x] == '1') // 北の壁
		{
			wall.y = (map_y + 1) * TILE_SIZE;
			wall.x = line_calc_x(ray.line, wall.y);
			draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), WALL_NORTH);
			return;
		}
		map_y++;
	}
}

/*
** DDAアルゴリズム 左向き
** レイと壁の交点を求める
** game: ゲーム構造体
** ray: レイ
** num: レイの番号
** angle: レイの角度
*/
void	dda_3(t_game *game, t_line_segment ray, int num, double angle)
{
	int			map_x;
	double		y;
	t_vector	wall;

	map_x = (int)(ray.start.x / TILE_SIZE);
	while (1)
	{
		y = line_calc_y(ray.line, map_x * TILE_SIZE) / TILE_SIZE;
		if (game->map_info->map[(int)y][map_x] == '1')
		{
			if (ray.start.y < ray.end.y) // 北の壁
			{
				wall.y = (int)y * TILE_SIZE;
				wall.x = line_calc_x(ray.line, wall.y);
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), WALL_NORTH);
			}
			else
			{
				wall.y = ((int)y + 1) * TILE_SIZE;
				wall.x = line_calc_x(ray.line, wall.y);
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), WALL_SOUTH);
			}
			return;
		}
		if (game->map_info->map[(int)y][map_x - 1] == '1') // 東の壁
		{
			wall.x = map_x * TILE_SIZE;
			wall.y = line_calc_y(ray.line, wall.x);
			draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), WALL_EAST);
			return;
		}
		map_x--;
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
	if (segment_direction(ray) == 0)
	{
		dda_0(game, ray, num, angle);
	}
	else if (segment_direction(ray) == 1)
	{
		dda_1(game, ray, num, angle);
	}
	else if (segment_direction(ray) == 2)
		dda_2(game, ray, num, angle);
	else
	{
		// 左向き
		dda_3(game, ray, num, angle);
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
	while (x > -(NUM_RAYS / 2))
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
