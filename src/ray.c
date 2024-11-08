/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:30:41 by kosnakam          #+#    #+#             */
/*   Updated: 2024/11/08 13:30:43 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_ray	ray_init(t_vector pos, t_vector dir)
{
	t_ray	ret;

	ret.pos = pos;
	ret.dir = dir;
	return (ret);
}

t_line	ray_to_line(t_ray ray)
{
	t_line	ret;

	if (ray.dir.x == 0)
	{
		ret.inclination = 0;
		ret.intercept = ray.pos.x;
		return (ret);
	}
	ret.inclination = ray.dir.y / ray.dir.x;
	ret.intercept = ray.pos.y - ret.inclination * ray.pos.x;
	return (ret);
}

t_line_segment	ray_to_segment(t_ray ray, double length)
{
	t_line_segment	ret;

	ret.start = ray.pos;
	ret.end.x = ray.pos.x + ray.dir.x * length;
	ret.end.y = ray.pos.y + ray.dir.y * length;
	ret.line = ray_to_line(ray);
	return (ret);
}

t_vector	ray_end(t_ray ray, double length)
{
	t_vector	ret;

	ret.x = ray.pos.x + ray.dir.x * length;
	ret.y = ray.pos.y + ray.dir.y * length;
	return (ret);
}
