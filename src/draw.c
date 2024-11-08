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

void	draw_rect(t_game *game, t_ray ray, t_wall wall, t_texture texture)
{
	int 	i;
	int 	src_y;
	int 	color;
	double	scale_y;

	i = 0;
	scale_y = (double)ray.dir.y / TILE_SIZE;
	if (ray.pos.x < 0)
		ray.pos.x = 0;
	if (ray.pos.x >= WIN_WIDTH)
		ray.pos.x = WIN_WIDTH - 1;
	while (i < ray.dir.y)
	{
		if (ray.pos.y + i < 0 || WIN_HEIGHT <= ray.pos.y + i)
		{
			i++;
			continue ;
		}
		src_y = (int)(i / scale_y);
		color = texture.data[(src_y) * (texture.width) + wall.x_pos];
		game->canvas.data[(int)(ray.pos.y + i) * WIN_WIDTH + (int)(ray.pos.x)] = color;
		i++;
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
	t_ray		ray;
	double		wall_height;
	// int			i = 0;

	// todo :50000マジックナンバー
	wall_height = 50000 / (wall.distance * cos(ray_angle));
	ray.pos = vector_init(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	ray.dir = vector_init(1, wall_height);
	ray.pos.x += ray_num;
	ray.pos.y -= ray.dir.y / 2;
	if (wall.color == WALL_NORTH)
		draw_rect(game, ray, wall, game->north);
	else if (wall.color == WALL_SOUTH)
		draw_rect(game, ray, wall, game->south);
	else if (wall.color == WALL_EAST)
		draw_rect(game, ray, wall, game->east);
	else
		draw_rect(game, ray, wall, game->west);
	// while (i < (WIN_HEIGHT - wall_height) / 2 )
	// {
	// 	game->canvas.data[i * WIN_WIDTH + (int)(ray.pos.x)] = game->map_info->c;
	// 	i++;
	// }
	// i = WIN_HEIGHT - 1;
	// while (i > (WIN_HEIGHT + wall_height) / 2 )
	// {
	// 	game->canvas.data[i * WIN_WIDTH + (int)(ray.pos.x)] = game->map_info->f;
	// 	i--;
	// }
}

