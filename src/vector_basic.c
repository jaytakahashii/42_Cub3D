/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:31:52 by kosnakam          #+#    #+#             */
/*   Updated: 2024/11/08 13:31:53 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vector	vector_init(double x, double y)
{
	t_vector	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

t_vector	vector_add(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return (ret);
}

t_vector	vector_sub(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return (ret);
}

t_vector	vector_mul(t_vector a, double b)
{
	t_vector	ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	return (ret);
}

t_vector	vector_div(t_vector a, double b)
{
	t_vector	ret;

	ret.x = a.x / b;
	ret.y = a.y / b;
	return (ret);
}
