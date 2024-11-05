#include "cub3D.h"

/*
** ベクトルの長さ
** a = (a.x, a.y)
** |a| = √(a.x^2 + a.y^2)
*/
double	vector_len(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

/*
** ベクトルの正規化 (長さを1にする)
** a = (a.x, a.y)
** |a| = √(a.x^2 + a.y^2)
** a / |a| = (a.x / |a|, a.y / |a|)
*/
t_vector	vector_normalize(t_vector a)
{
	double	len;

	len = vector_len(a);
	return (vector_div(a, len));
}

/*
** ベクトルの内積
** a = (a.x, a.y)
** b = (b.x, b.y)
** a・b = a.x * b.x + a.y * b.y
*/
double	vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y);
}

/*
** ベクトルの外積
** a = (a.x, a.y)
** b = (b.x, b.y)
** a×b = a.x * b.y - a.y * b.x
*/
double	vector_cross(t_vector a, t_vector b)
{
	return (a.x * b.y - a.y * b.x);
}

/*
** ベクトルの回転
** a = (a.x, a.y)
** angle = 回転角度
** (a.x * cos(angle) - a.y * sin(angle), a.x * sin(angle) + a.y * cos(angle))
*/
t_vector	vector_rotate(t_vector a, double angle)
{
	t_vector	ret;

	ret.x = a.x * cos(angle) - a.y * sin(angle);
	ret.y = a.x * sin(angle) + a.y * cos(angle);
	return (ret);
}
