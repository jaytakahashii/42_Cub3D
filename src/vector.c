/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:32:08 by kosnakam          #+#    #+#             */
/*   Updated: 2024/11/08 13:32:09 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	vector_len(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

t_vector	vector_normalize(t_vector a)
{
	double	len;

	len = vector_len(a);
	return (vector_div(a, len));
}

double	vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y);
}

double	vector_cross(t_vector a, t_vector b)
{
	return (a.x * b.y - a.y * b.x);
}

t_vector	vector_rotate(t_vector a, double angle)
{
	t_vector	ret;

	ret.x = a.x * cos(angle) - a.y * sin(angle);
	ret.y = a.x * sin(angle) + a.y * cos(angle);
	return (ret);
}
