/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:32:15 by kosnakam          #+#    #+#             */
/*   Updated: 2024/12/04 15:01:57 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	wall_spell_check(char **map, int y, int x, int height)
{
	if (y + 1 >= height || y - 1 < 0 || x + 1 > (int)ft_strlen(map[y])
		|| x - 1 < 0)
		return (1);
	if (!map[y + 1][x] || !map[y - 1][x] || !map[y][x + 1]
		|| !map[y][x - 1])
		return (1);
	if (ft_isspace(map[y + 1][x]) || ft_isspace(map[y - 1][x])
		|| ft_isspace(map[y][x + 1]) || ft_isspace(map[y][x - 1]))
		return (1);
	return (0);
}

void	wall_check(t_map *map_info, int y, int x)
{
	map_info->count += 1;
	if (map_info->count > MAP_SIZE)
	{
		map_info->flag = 1;
		return ;
	}
	if (!map_info->map_tmp || !map_info->map_tmp[y]
		|| !map_info->map_tmp[y][x] || map_info->map_tmp[y][x] == '1')
		return ;
	else
	{
		map_info->map_tmp[y][x] = '1';
		if (wall_spell_check(map_info->map_tmp, y, x, map_info->height))
		{
			map_info->flag = 1;
			return ;
		}
		wall_check(map_info, y + 1, x);
		wall_check(map_info, y - 1, x);
		wall_check(map_info, y, x + 1);
		wall_check(map_info, y, x - 1);
	}
}
