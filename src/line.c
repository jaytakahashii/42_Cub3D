/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:16 by kosnakam          #+#    #+#             */
/*   Updated: 2024/11/08 13:29:18 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_line	line_from_points(t_vector vec1, t_vector vec2)
{
	t_line	ret;

	if (vec2.x - vec1.x == 0)
	{
		ret.inclination = 0;
		ret.intercept = vec1.x;
		return (ret);
	}
	ret.inclination = (vec2.y - vec1.y) / (vec2.x - vec1.x);
	ret.intercept = vec1.y - ret.inclination * vec1.x;
	return (ret);
}

double	line_calc_y(t_line line, double x)
{
	if (line.inclination == 0)
		return (line.intercept);
	return (line.inclination * x + line.intercept);
}

double	line_calc_x(t_line line, double y)
{
	if (line.inclination == 0)
		return (line.intercept);
	return ((y - line.intercept) / line.inclination);
}

double	line_calc(t_line line, double x, double y, bool is_x)
{
	if (is_x)
		return (line_calc_y(line, x));
	return (line_calc_x(line, y));
}
