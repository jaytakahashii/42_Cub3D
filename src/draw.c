/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:28:15 by kosnakam          #+#    #+#             */
/*   Updated: 2024/12/04 15:02:32 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	draw_line(t_game *game, t_ray ray, t_wall wall, t_texture texture)
{
	int		i;
	int		src_y;
	int		color;
	double	scale_y;

	i = 0;
	scale_y = (double)ray.dir.y / TEXTURE_SIZE;
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
		game->canvas.data[(int)(ray.pos.y + i)
			*WIN_WIDTH + (int)(ray.pos.x)] = color;
		i++;
	}
}

void	draw_wall(t_game *game, t_wall wall, int ray_num, double ray_angle)
{
	t_ray		ray;
	double		wall_height;

	wall_height = RATE / (wall.distance * cos(ray_angle));
	ray.pos = vector_init(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	ray.dir = vector_init(1, wall_height);
	ray.pos.x += ray_num;
	ray.pos.y -= ray.dir.y / 2;
	if (wall.color == WALL_NORTH)
		draw_line(game, ray, wall, game->north);
	else if (wall.color == WALL_SOUTH)
		draw_line(game, ray, wall, game->south);
	else if (wall.color == WALL_EAST)
		draw_line(game, ray, wall, game->east);
	else
		draw_line(game, ray, wall, game->west);
}
