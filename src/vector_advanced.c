/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:40:39 by jtakahas          #+#    #+#             */
/*   Updated: 2024/12/11 13:40:40 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** 角度からベクトルを作成
** angle = 角度
** (cos(angle), sin(angle))
*/
t_vector	vector_from_angle(double angle)
{
	t_vector	ret;

	ret.x = cos(angle);
	ret.y = sin(angle);
	return (ret);
}

/*
** ベクトルの角度
** a = (a.x, a.y)
** atan2(a.y, a.x)
*/
double	vector_angle(t_vector a)
{
	return (atan2(a.y, a.x));
}

/*
** 2点間のベクトル
** from = (from.x, from.y)
** to = (to.x, to.y)
** to - from = (to.x - from.x, to.y - from.y)
*/
t_vector	vector_from_to(t_vector from, t_vector to)
{
	t_vector	ret;

	ret.x = to.x - from.x;
	ret.y = to.y - from.y;
	return (ret);
}
