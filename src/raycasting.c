/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:30:57 by kosnakam          #+#    #+#             */
/*   Updated: 2024/11/08 15:58:34 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	if (wall.color == WALL_EAST || wall.color == WALL_WEST)
		wall.x_pos = (int)wall.pos.y % TEXTURE_SIZE;
	else
		wall.x_pos = (int)wall.pos.x % TEXTURE_SIZE;
	draw_wall(game, wall, num, angle);
}

void	raycasting(t_game *game, t_player *player)
{
	t_line_segment	ray;
	int				i;
	double			angle_step;
	t_vector		dir;

	angle_step = FOV_ANGLE / NUM_RAYS;
	i = NUM_RAYS / 2;
	while (i >= -(NUM_RAYS / 2))
	{
		dir = vector_rotate(player->dir, i * angle_step);
		ray = ray_to_segment(ray_init(player->pos, dir), VIEW_DISTANCE);
		check_wall(game, ray, i, i * angle_step);
		i--;
	}
}
