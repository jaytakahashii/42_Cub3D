#include "cub3D.h"

static void	wall_set(t_wall *wall, double x, double y, int color)
{
	if (0 <= x)
		wall->pos.x = x;
	if (0 <= y)
		wall->pos.y = y;
	if (0 <= color)
		wall->color = color;
}

/*
** DDAアルゴリズム 上向き
** レイと壁の交点を求める
** game: ゲーム構造体
** ray: レイ
** num: レイの番号
** angle: レイの角度
*/
t_wall	dda_up(t_game *game, t_line_segment ray)
{
	double	x;
	t_wall	wall;

	wall_set(&wall, -1, -1, -1);
	int (map_y) = (int)(ray.start.y / TEXTURE_SIZE) + 1;
	while (0 <= --map_y)
	{
		x = (line_calc_x(ray.line, map_y * TEXTURE_SIZE) / TEXTURE_SIZE);
		if (game->map_info->map[map_y][(int)x] == '1')
		{
			if (ray.start.x < ray.end.x)
				wall_set(&wall, (int)x * TEXTURE_SIZE, -1, WALL_WEST);
			else
				wall_set(&wall, ((int)x + 1) * TEXTURE_SIZE, -1, WALL_EAST);
			wall.pos.y = line_calc_y(ray.line, wall.pos.x);
			break ;
		}
		if (game->map_info->map[map_y - 1][(int)x] == '1')
		{
			wall_set(&wall, -1, map_y * TEXTURE_SIZE, WALL_SOUTH);
			wall.pos.x = line_calc_x(ray.line, wall.pos.y);
			break ;
		}
	}
	return (wall);
}

/*
** DDAアルゴリズム 右向き
** レイと壁の交点を求める
** game: ゲーム構造体
** ray: レイ
** num: レイの番号
** angle: レイの角度
*/
t_wall	dda_right(t_game *game, t_line_segment ray)
{
	double	y;
	t_wall	wall;

	wall_set(&wall, -1, -1, -1);
	int (map_x) = (int)(ray.start.x / TEXTURE_SIZE);
	while (++map_x <= WIN_WIDTH)
	{
		y = line_calc_y(ray.line, map_x * TEXTURE_SIZE) / TEXTURE_SIZE;
		if (game->map_info->map[(int)y][map_x - 1] == '1')
		{
			if (ray.start.y < ray.end.y)
				wall_set(&wall, -1, (int)y * TEXTURE_SIZE, WALL_NORTH);
			else
				wall_set(&wall, -1, ((int)y + 1) * TEXTURE_SIZE, WALL_SOUTH);
			wall.pos.x = line_calc_x(ray.line, wall.pos.y);
			break ;
		}
		if (game->map_info->map[(int)y][map_x] == '1')
		{
			wall_set(&wall, map_x * TEXTURE_SIZE, -1, WALL_WEST);
			wall.pos.y = line_calc_y(ray.line, wall.pos.x);
			break ;
		}
	}
	return (wall);
}

/*
** DDAアルゴリズム 下向き
** レイと壁の交点を求める
** game: ゲーム構造体
** ray: レイ
** num: レイの番号
** angle: レイの角度
*/
t_wall	dda_down(t_game *game, t_line_segment ray)
{
	double	x;
	t_wall	wall;

	wall_set(&wall, -1, -1, -1);
	int (map_y) = (int)(ray.start.y / TEXTURE_SIZE) - 1;
	while (++map_y < WIN_HEIGHT)
	{
		x = line_calc_x(ray.line, (map_y + 1) * TEXTURE_SIZE) / TEXTURE_SIZE;
		if (game->map_info->map[map_y][(int)x] == '1')
		{
			if (ray.start.x < ray.end.x)
				wall_set(&wall, (int)x * TEXTURE_SIZE, -1, WALL_WEST);
			else
				wall_set(&wall, ((int)x + 1) * TEXTURE_SIZE, -1, WALL_EAST);
			wall.pos.y = line_calc_y(ray.line, wall.pos.x);
			break ;
		}
		if (game->map_info->map[map_y + 1][(int)x] == '1')
		{
			wall_set(&wall, -1, (map_y + 1) * TEXTURE_SIZE, WALL_NORTH);
			wall.pos.x = line_calc_x(ray.line, wall.pos.y);
			break ;
		}
	}
	return (wall);
}

/*
** DDAアルゴリズム 左向き
** レイと壁の交点を求める
** game: ゲーム構造体
** ray: レイ
** num: レイの番号
** angle: レイの角度
*/
t_wall	dda_left(t_game *game, t_line_segment ray)
{
	double	y;
	t_wall	wall;

	wall_set(&wall, -1, -1, -1);
	int (map_x) = (int)(ray.start.x / TEXTURE_SIZE) + 1;
	while (0 <= --map_x)
	{
		y = line_calc_y(ray.line, map_x * TEXTURE_SIZE) / TEXTURE_SIZE;
		if (game->map_info->map[(int)y][map_x] == '1')
		{
			if (ray.start.y < ray.end.y)
				wall_set(&wall, -1, (int)y * TEXTURE_SIZE, WALL_NORTH);
			else
				wall_set(&wall, -1, ((int)y + 1) * TEXTURE_SIZE, WALL_SOUTH);
			wall.pos.x = line_calc_x(ray.line, wall.pos.y);
			break ;
		}
		if (game->map_info->map[(int)y][map_x - 1] == '1')
		{
			wall_set(&wall, map_x * TEXTURE_SIZE, -1, WALL_EAST);
			wall.pos.y = line_calc_y(ray.line, wall.pos.x);
			break ;
		}
	}
	return (wall);
}
