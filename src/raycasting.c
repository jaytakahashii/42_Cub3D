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
	double	angle;

	angle = atan2(line.end.y - line.start.y, line.end.x - line.start.x);
	if (angle >= -M_PI / 4 && angle < M_PI / 4)
		return (1);
	else if (angle >= M_PI / 4 && angle < 3 * M_PI / 4)
		return (0);
	else if (angle >= 3 * M_PI / 4 || angle < -3 * M_PI / 4)
		return (3);
	else
		return (2);
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
	int			map_x;
	int			map_y;
	t_vector	wall;

	map_y = (int)(ray.start.y / TILE_SIZE);
	while (1)
	{
		map_x = (int)(line_calc_x(ray.line, map_y * TILE_SIZE) / TILE_SIZE);
		if (game->map_info->map[map_y][map_x] == '1')
		{
			map_x++;
			wall.y = line_calc_y(ray.line, map_x * TILE_SIZE);
			wall.x = map_x * TILE_SIZE;
			if (ray.start.x < wall.x) // 西の壁
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), MGREEN);
			else // 東の壁
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), MBLUE);
			return;
		}
		if (game->map_info->map[map_y - 1][map_x] == '1') // 南の壁
		{
			wall.y = map_y * TILE_SIZE;
			wall.x = line_calc_x(ray.line, map_y * TILE_SIZE);
			draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), MWHITE);
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
	int			map_y;
	t_vector	wall;

	map_x = (int)(ray.start.x / TILE_SIZE);
	while (1)
	{
		map_y = (int)(line_calc_y(ray.line, map_x * TILE_SIZE) / TILE_SIZE);
		if (game->map_info->map[map_y][map_x] == '1')
		{
			map_y++;
			wall.y = map_y * TILE_SIZE;
			wall.x = line_calc_x(ray.line, map_y * TILE_SIZE);
			if (ray.start.y < wall.y) // 北の壁
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), MYELLOW);
			else // 南の壁
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), MWHITE);
			return;
		}
		if (game->map_info->map[map_y][map_x + 1] == '1') // 西の壁
		{
			wall.y = line_calc_y(ray.line, (map_x + 1) * TILE_SIZE);
			wall.x = (map_x + 1) * TILE_SIZE;
			draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), MGREEN);
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
	int			map_x;
	int			map_y;
	t_vector	wall;

	map_y = (int)(ray.start.y / TILE_SIZE);
	while (1)
	{
		map_x = (int)(line_calc_x(ray.line, map_y * TILE_SIZE) / TILE_SIZE);
		if (game->map_info->map[map_y][map_x] == '1')
		{
			map_x++;
			wall.y = line_calc_y(ray.line, map_x * TILE_SIZE);
			wall.x = map_x * TILE_SIZE;
			if (ray.start.x < wall.x) // 西の壁
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), MGREEN);
			else // 東の壁
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), MBLUE);
			return;
		}
		if (game->map_info->map[map_y + 1][map_x] == '1') // 北の壁
		{
			wall.y = map_y * TILE_SIZE;
			wall.x = line_calc_x(ray.line, map_y * TILE_SIZE);
			draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), MYELLOW);
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
	int			map_y;
	t_vector	wall;

	map_x = (int)(ray.start.x / TILE_SIZE);
	while (1)
	{
		map_y = (int)(line_calc_y(ray.line, map_x * TILE_SIZE) / TILE_SIZE);
		if (game->map_info->map[map_y][map_x] == '1')
		{
			map_y++;
			wall.y = map_y * TILE_SIZE;
			wall.x = line_calc_x(ray.line, map_y * TILE_SIZE);
			if (ray.start.y < wall.y) // 北の壁
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), MYELLOW);
			else // 南の壁
				draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), MWHITE);
			return;
		}
		if (game->map_info->map[map_y][map_x - 1] == '1') // 東の壁
		{
			wall.y = line_calc_y(ray.line, (map_x - 1) * TILE_SIZE);
			wall.x = (map_x - 1) * TILE_SIZE;
			draw_wall(game, num, angle, vector_len(vector_from_to(ray.start, wall)), MBLUE);
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
		// 右向き
		dda_1(game, ray, num, angle);
	}
	else if (segment_direction(ray) == 2)
	{
		// 下向き
		dda_2(game, ray, num, angle);
	}
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
	double			angle_step;
	t_vector		dir;
	int				x;

	x = 1;
	angle_step = FOV_ANGLE / NUM_RAYS;
	ray = ray_to_segment(ray_init(player->pos, player->dir), VIEW_DISTANCE);
	check_wall(game, ray, 0, 0);
	while (x <= NUM_RAYS / 2)
	{
		dir = vector_rotate(player->dir, x * angle_step);
		ray = ray_to_segment(ray_init(player->pos, dir), VIEW_DISTANCE);
		check_wall(game, ray, x, x * angle_step);
		dir = vector_rotate(player->dir, -x * angle_step);
		ray = ray_to_segment(ray_init(player->pos, dir), VIEW_DISTANCE);
		check_wall(game, ray, x * -1, x * -angle_step);
		x++;
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

	rate = 10000 / (distance * cos(angle));
	start = vector_init(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	size = vector_init(1, rate);
	start.x += num;
	draw_rect(game, start, size, color);
}
