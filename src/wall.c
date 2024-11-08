/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:32:15 by kosnakam          #+#    #+#             */
/*   Updated: 2024/11/08 14:38:02 by kosnakam         ###   ########.fr       */
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

void	wall_check(t_map *map_info, int y, int x)
{
	map_info->count += 1;
	if (map_info->count > 10000)
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
		if (wall_spell_check(map_info->map_tmp, y, x))
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
