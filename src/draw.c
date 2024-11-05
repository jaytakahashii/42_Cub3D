#include "cub3D.h"

/*
*/
static void	check_condition(t_ray *ray, double length, t_line_condition *cond)
{
	t_vector	end;

	end.x = ray->pos.x + ray->dir.x * length;
	end.y = ray->pos.y + ray->dir.y * length;
	if (fabs(ray->dir.x) > fabs(ray->dir.y))
	{
		cond->is_x_major = true;
		cond->puls = &ray->pos.x;
		if (ray->dir.x > 0)
			cond->move = 1;
		else
			cond->move = -1;
		cond->condition = fabs(ray->pos.x - end.x);
	}
	else
	{
		cond->is_x_major = false;
		cond->puls = &ray->pos.y;
		if (ray->dir.y > 0)
			cond->move = 1;
		else
			cond->move = -1;
		cond->condition = fabs(ray->pos.y - end.y);
	}
}

/*
** 線分の描画
** game: ゲーム構造体
** t_ray: レイ構造体 (始点と方向)
** length: 線分の長さ
** color: 色
*/
void	draw_line(t_game *game, t_ray ray, double length, int color)
{
	t_line				line;
	t_line_condition	cond;
	t_vector			draw_pos;

	line = line_from_points(ray.pos, ray_end(ray, length));
	check_condition(&ray, length, &cond);
	while ((cond.condition)-- > 0)
	{
		if (cond.is_x_major)
			draw_pos = vector_init(ray.pos.x, line_calc_y(line, ray.pos.x));
		else
			draw_pos = vector_init(line_calc_x(line, ray.pos.y), ray.pos.y);
		if (out_of_window(draw_pos))
		{
			*(cond.puls) += cond.move;
			continue ;
		}
		game->canvas.data[(int)draw_pos.y * WIN_WIDTH
			+ (int)draw_pos.x] = color;
		*(cond.puls) += cond.move;
	}
}

/*
** 円の描画
** game: ゲーム構造体
** point: 円の中心座標(t_vector.x: x座標, t_vector.y: y座標)
** radius: 半径
** color: 色
*/
void	draw_circle(t_game *game, t_vector point, int radius, int color)
{
	int	i;
	int	j;

	i = -radius;
	while (i < radius)
	{
		j = -radius;
		while (j < radius)
		{
			if (i * i + j * j < radius * radius)
				mlx_pixel_put(game->mlx, game->win, point.x + i, point.y + j,
					color);
			j++;
		}
		i++;
	}
}

/*
** 長方形の描画（塗りつぶし）
** game: ゲーム構造体
** pos: 長方形の真ん中の座標
** size: 長方形の大きさ (t_vector.x: 幅, t_vector.y: 高さ)
** color: 色
*/

// void	draw_rect(t_game *game, t_vector pos, t_vector size, int kolor, int y)
// {
// 	int		j;

// 	kolor = 0x00FF0000;
// 	if (pos.x < 0)
// 		pos.x = 0;
// 	if (pos.x >= WIN_WIDTH)
// 		pos.x = WIN_WIDTH - 1;
// 	if (pos.y < 0)
// 		pos.y = 0;
// 	if (pos.y >= WIN_HEIGHT)
// 		pos.y = WIN_HEIGHT - 1;
// 	j = -size.y / 2;
// 	double scale_x = (double)size.y / TILE_SIZE;
// 	// double scale_y = (double)size / TILE_SIZE;
// 	// ft_printf("scale_x: %d\n", (int)scale_x);
// 	while (j < size.y / 2)
// 	{
// 		if (pos.y + j < 0 || pos.y + j >= WIN_HEIGHT)
// 		{
// 			j++;
// 			continue ;
// 		}
// 		int src_x = (int)(j / scale_x);
// 		// int src_y = (int)(y / scale_y);
// 		// ft_printf("src_x: %d\n", src_x);
// 		// ft_printf("src_x * game->north.width + y: %d\n", src_x * game->north.width + y);
// 		int color = game->north.data[src_x + y* (game->north.width)];
// 		game->canvas.data[(int)(pos.y + j) * WIN_WIDTH + (int)(pos.x)] = color;
// 		j++;
// 	}
// }

void	draw_rect(t_game *game, t_vector pos, t_vector size, int color)
{
	int	j;

	if (pos.x < 0)
		pos.x = 0;
	if (pos.x >= WIN_WIDTH)
		pos.x = WIN_WIDTH - 1;
	j = -size.y / 2;
	double scale_y = (double)size.y / TILE_SIZE;
	while (j < size.y / 2)
	{
		if (pos.y + j < 0 || pos.y + j >= WIN_HEIGHT)
		{
			j++;
			continue ;
		}
		int src_y = (int)(j / scale_y);
		if (src_y < 0)
			src_y *= -1;
		// ft_printf("j: %d\n", j);
		color = game->north.data[(src_y) * (game->north.width) + game->x];
		game->canvas.data[(int)(pos.y + j) * WIN_WIDTH + (int)(pos.x)] = color;
		j++;
	}
}

/*
** 壁を描画する関数
** game: ゲーム構造体
** num: レイの番号
** angle: レイの角度
** distance: 壁までの距離
*/
void	draw_wall(t_game *game, t_wall wall, int ray_num, double ray_angle)
{
	t_vector	start;
	t_vector	size;
	double		rate;

	rate = 50000 / (wall.distance * cos(ray_angle));
	start = vector_init(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	size = vector_init(1, rate);
	start.x += ray_num;
	draw_rect(game, start, size, wall.color);
}
