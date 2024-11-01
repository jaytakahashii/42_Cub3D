#include "cub3D.h"

// window.c

/*
** ウィンドウの初期化
** game: ゲーム構造体
*/
void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	game->canvas.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->canvas.data = (int *)mlx_get_data_addr(game->canvas.img, &game->canvas.bpp, &game->canvas.size_line, &game->canvas.endian);
}

/*
** ウィンドウの削除
** game: ゲーム構造体
*/
int	window_exit(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

/*
** 線分の描画
** game: ゲーム構造体
** t_ray: レイ構造体 (始点と方向)
** length: 線分の長さ
** color: 色
*/
void	mlx_line_put(t_game *game, t_ray ray, double length, int color)
{
	t_vector	end;
	t_line		line;

	end.x = ray.pos.x + ray.dir.x * length;
	end.y = ray.pos.y + ray.dir.y * length;
	line = line_from_points(ray.pos, end);
	if (fabs(ray.dir.x) > fabs(ray.dir.y))
	{
		if (ray.dir.x > 0)
		{
			while (ray.pos.x < end.x)
			{
				if (ray.pos.x < 0 || ray.pos.x >= WIN_WIDTH || line_calc_y(line, ray.pos.x) < 0 || line_calc_y(line, ray.pos.x) >= WIN_HEIGHT)
				{
					ray.pos.x++;
					continue ;
				}
				// mlx_pixel_put(game->mlx, game->win, ray.pos.x, line_calc_y(line, ray.pos.x), color);
				game->canvas.data[(int)line_calc_y(line, ray.pos.x) * WIN_WIDTH + (int)ray.pos.x] = color;
				ray.pos.x++;
			}
		}
		else
		{
			while (ray.pos.x > end.x)
			{
				if (ray.pos.x < 0 || ray.pos.x >= WIN_WIDTH || line_calc_y(line, ray.pos.x) < 0 || line_calc_y(line, ray.pos.x) >= WIN_HEIGHT)
				{
					ray.pos.x--;
					continue ;
				}
				// mlx_pixel_put(game->mlx, game->win, ray.pos.x, line_calc_y(line, ray.pos.x), color);
				game->canvas.data[(int)line_calc_y(line, ray.pos.x) * WIN_WIDTH + (int)ray.pos.x] = color;
				ray.pos.x--;
			}
		}
	}
	else
	{
		if (ray.dir.y > 0)
		{
			while (ray.pos.y < end.y)
			{
				if (ray.pos.y < 0 || ray.pos.y >= WIN_HEIGHT || line_calc_x(line, ray.pos.y) < 0 || line_calc_x(line, ray.pos.y) >= WIN_WIDTH)
				{
					ray.pos.y++;
					continue ;
				}
				// mlx_pixel_put(game->mlx, game->win, line_calc_x(line, ray.pos.y), ray.pos.y, color);
				game->canvas.data[(int)ray.pos.y * WIN_WIDTH + (int)line_calc_x(line, ray.pos.y)] = color;
				ray.pos.y++;
			}
		}
		else
		{
			while (ray.pos.y > end.y)
			{
				if (ray.pos.y < 0 || ray.pos.y >= WIN_HEIGHT || line_calc_x(line, ray.pos.y) < 0 || line_calc_x(line, ray.pos.y) >= WIN_WIDTH)
				{
					ray.pos.y--;
					continue ;
				}
				// mlx_pixel_put(game->mlx, game->win, line_calc_x(line, ray.pos.y), ray.pos.y, color);
				// ray.pos.yが一定のところで-1となり、セグフォが起こる
				game->canvas.data[(int)ray.pos.y * WIN_WIDTH + (int)line_calc_x(line, ray.pos.y)] = color;
				ray.pos.y--;
			}
		}
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
	int		i;
	int		j;

	i = -radius;
	while (i < radius)
	{
		j = -radius;
		while (j < radius)
		{
			if (i * i + j * j < radius * radius)
				mlx_pixel_put(game->mlx, game->win, point.x + i, point.y + j, color);
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
void	draw_rect(t_game *game, t_vector pos, t_vector size, int kolor, int y)
{
	int		j;

	kolor = 0x00FF0000;
	if (pos.x < 0)
		pos.x = 0;
	if (pos.x >= WIN_WIDTH)
		pos.x = WIN_WIDTH - 1;
	if (pos.y < 0)
		pos.y = 0;
	if (pos.y >= WIN_HEIGHT)
		pos.y = WIN_HEIGHT - 1;
	j = -size.y / 2;
	double scale_x = (double)size.y / TILE_SIZE;
	// double scale_y = (double)size / TILE_SIZE;
	// ft_printf("scale_x: %d\n", (int)scale_x);
	while (j < size.y / 2)
	{
		if (pos.y + j < 0 || pos.y + j >= WIN_HEIGHT)
		{
			j++;
			continue ;
		}
		int src_x = (int)(j / scale_x);
		// int src_y = (int)(y / scale_y);
		// ft_printf("src_x: %d\n", src_x);
		// ft_printf("src_x * game->north.width + y: %d\n", src_x * game->north.width + y);
		int color = game->north.data[src_x + y* (game->north.width)];
		game->canvas.data[(int)(pos.y + j) * WIN_WIDTH + (int)(pos.x)] = color;
		j++;
	}
}
