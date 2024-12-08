/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:31:27 by kosnakam          #+#    #+#             */
/*   Updated: 2024/11/08 13:31:28 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vector	vector_from_angle(double angle)
{
	t_vector	ret;

	ret.x = cos(angle);
	ret.y = sin(angle);
	return (ret);
}

double	vector_angle(t_vector a)
{
	return (atan2(a.y, a.x));
}

t_vector	vector_from_to(t_vector from, t_vector to)
{
	t_vector	ret;

	ret.x = to.x - from.x;
	ret.y = to.y - from.y;
	return (ret);
}
