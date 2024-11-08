/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:32:15 by kosnakam          #+#    #+#             */
/*   Updated: 2024/11/08 13:32:16 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	wall_spell_check(char **map, int y, int x)
{
	if (!map[y + 1][x] || !map[y - 1][x] || !map[y][x + 1]
		|| !map[y][x - 1])
		return (1);
	if (ft_isspace(map[y + 1][x]) || ft_isspace(map[y - 1][x])
		|| ft_isspace(map[y][x + 1]) || ft_isspace(map[y][x - 1]))
		return (1);
	return (0);
}

void	wall_check(char **map, int y, int x, unsigned int *count, int *flag)
{
	*count += 1;
	// todo: ほんとに一萬でいいか議論
	if (*count > 10000)
	{
		*flag = 1;
		return ;
	}
	if (!map || !map[y] || !map[y][x] || map[y][x] == '1')
		return ;
	else
	{
		map[y][x] = '1';
		if (wall_spell_check(map, y, x))
		{
			*flag = 1;
			return ;
		}
		wall_check(map, y + 1, x, count, flag);
		wall_check(map, y - 1, x, count, flag);
		wall_check(map, y, x + 1, count, flag);
		wall_check(map, y, x - 1, count, flag);
	}
}
