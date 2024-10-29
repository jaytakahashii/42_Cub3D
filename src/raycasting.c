#include "cub3D.h"

// raycasting.c

void	check_wall(t_game *game, t_line_segment ray, int num, double angle)
{
	printf("ray.start.x: %f, ray.start.y: %f\n", ray.start.x, ray.start.y);
	printf("ray.end.x: %f, ray.end.y: %f\n", ray.end.x, ray.end.y);
	printf("ray.line.inclination: %f\n", ray.line.inclination);
	if (-1 <= ray.line.inclination && ray.line.inclination <= 1
		&& ray.start.x <= ray.end.x)
	{
		printf("%d\n", 1);
	}
	else if (-1 <= ray.line.inclination && ray.line.inclination <= 1
		&& ray.start.x > ray.end.x)
	{
		printf("%d\n", 3);
	}
	else if (ray.start.y <= ray.end.y)
	{
		printf("%d\n", 4);
	}
	else
	{
		printf("%d\n", 2);
	}
	(void)game;
	(void)num;
	(void)angle;
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
	angle_step = FOV_ANGLE_HALF / NUM_RAYS;
	ray = ray_to_segment(ray_init(player->pos, player->dir), VIEW_DISTANCE);
	check_wall(game, ray, 0, 0);
	while (x <= NUM_RAYS)
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
void	draw_wall(t_game *game, int num, double angle, double distance)
{
	t_vector	start;
	t_vector	size;
	double		rate;

	rate = 10000 / (distance * cos(angle));
	start = vector_init(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	size = vector_init(1, rate);
	start.x += num;
	draw_rect(game, start, size, MBLUE);
}
