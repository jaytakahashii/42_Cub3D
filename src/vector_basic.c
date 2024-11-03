#include "cub3D.h"

/*
** ベクトルの初期化
** x, y: ベクトルの座標
*/
t_vector	vector_init(double x, double y)
{
	t_vector	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

/*
** ベクトルの足し算
** a = (a.x, a.y)
** b = (b.x, b.y)
** a + b = (a.x + b.x, a.y + b.y)
*/
t_vector	vector_add(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return (ret);
}

/*
** ベクトルの引き算
** a = (a.x, a.y)
** b = (b.x, b.y)
** a - b = (a.x - b.x, a.y - b.y)
*/
t_vector	vector_sub(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return (ret);
}

/*
** ベクトルのスカラー倍
** a = (a.x, a.y)
** b = スカラー
** a * b = (a.x * b, a.y * b)
*/
t_vector	vector_mul(t_vector a, double b)
{
	t_vector	ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	return (ret);
}

/*
** ベクトルのスカラー倍
** a = (a.x, a.y)
** b = スカラー
** a / b = (a.x / b, a.y / b)
*/
t_vector	vector_div(t_vector a, double b)
{
	t_vector	ret;

	ret.x = a.x / b;
	ret.y = a.y / b;
	return (ret);
}
