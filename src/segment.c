/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:31:09 by kosnakam          #+#    #+#             */
/*   Updated: 2024/11/08 13:31:11 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_line_segment	line_segment_init(t_vector start, t_vector end)
{
	t_line_segment	ret;

	ret.start = start;
	ret.end = end;
	ret.line = line_from_points(start, end);
	return (ret);
}

bool	is_intersect(t_line_segment line1, t_line_segment line2)
{
	if ((line1.start.x <= line2.start.x && line2.start.x <= line1.end.x)
		|| (line1.start.x <= line2.end.x && line2.end.x <= line1.end.x))
	{
		if ((line1.start.y <= line2.start.y && line2.start.y <= line1.end.y)
			|| (line1.start.y <= line2.end.y && line2.end.y <= line1.end.y))
			return (true);
	}
	return (false);
}

t_vector	line_intersection(t_line_segment line1, t_line_segment line2)
{
	double		det;
	double		t;
	double		s;
	t_vector	ret;

	det = (line1.end.x - line1.start.x) * (line2.end.y - line2.start.y)
		- (line1.end.y - line1.start.y) * (line2.end.x - line2.start.x);
	t = ((line2.start.x - line1.start.x) * (line2.end.y - line2.start.y)
			- (line2.start.y - line1.start.y) * (line2.end.x - line2.start.x))
		/ det;
	s = ((line2.start.x - line1.start.x) * (line1.end.y - line1.start.y)
			- (line2.start.y - line1.start.y) * (line1.end.x - line1.start.x))
		/ det;
	ret.x = line1.start.x + t * (line1.end.x - line1.start.x);
	ret.y = line1.start.y + t * (line1.end.y - line1.start.y);
	if (t < 0 || t > 1 || s < 0 || s > 1)
		ret = vector_init(-1, -1);
	return (ret);
}
