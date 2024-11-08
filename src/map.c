/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:28 by kosnakam          #+#    #+#             */
/*   Updated: 2024/11/08 14:38:39 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	map_info_init(t_map **map_info, t_allocations **alloc)
{
	*map_info = (t_map *)malloxit(sizeof(t_map), alloc);
	(*map_info)->map = (char **)malloxit(sizeof(char *) * OPEN_MAX, alloc);
	(*map_info)->map_tmp = (char **)malloxit(sizeof(char *) * OPEN_MAX, alloc);
	(*map_info)->map[OPEN_MAX] = NULL;
	(*map_info)->no = NULL;
	(*map_info)->so = NULL;
	(*map_info)->we = NULL;
	(*map_info)->ea = NULL;
	(*map_info)->f = -1;
	(*map_info)->c = -1;
}

int	set_path(char **target, char *map, t_allocations **alloc)
{
	int	i;

	i = 0;
	map += 2;
	if (!ft_isspace(*map))
		return (1);
	pass_space(&map);
	*target = ft_strdup(map, alloc);
	while (1)
	{
		if ((*target)[i] == '\n' || (*target)[i] == 0)
		{
			(*target)[i] = 0;
			break ;
		}
		i++;
	}
	return (0);
}

int	set_color(int *target, char *map, t_allocations **alloc)
{
	int	i;
	int	*rgb;

	i = -1;
	map += 1;
	if (!ft_isspace(*map))
		return (1);
	rgb = (int *)malloxit(sizeof(int) * 3, alloc);
	pass_space(&map);
	while (++i < 3)
	{
		rgb[i] = ft_atoi(map);
		while (ft_isdigit(*map))
			map++;
		if (*map == ',' || *map == '\n')
			map++;
		else
			return (1);
	}
	*target = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (0);
}

int	set_map_info(t_map *map_info, char *map, t_allocations **alloc)
{
	if (ft_strncmp(map, "NO", 2) == 0)
		return (set_path(&map_info->no, map, alloc));
	else if (ft_strncmp(map, "SO", 2) == 0)
		return (set_path(&map_info->so, map, alloc));
	else if (ft_strncmp(map, "WE", 2) == 0)
		return (set_path(&map_info->we, map, alloc));
	else if (ft_strncmp(map, "EA", 2) == 0)
		return (set_path(&map_info->ea, map, alloc));
	else if (ft_strncmp(map, "F", 1) == 0)
		return (set_color(&map_info->f, map, alloc));
	else if (ft_strncmp(map, "C", 1) == 0)
		return (set_color(&map_info->c, map, alloc));
	return (1);
}

void	map_scan(t_game *game, char *argv)
{
	char	*line;

	int (y) = 0;
	int (fd) = ft_open(argv);
	map_info_init(&game->map_info, &(game->alloc));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n'
			|| !set_map_info(game->map_info, line, &(game->alloc)))
		{
			free(line);
			continue ;
		}
		game->map_info->map[y] = ft_strdup(line, &(game->alloc));
		game->map_info->map_tmp[y] = ft_strdup(line, &(game->alloc));
		free(line);
		y++;
	}
	game->map_info->map[y] = NULL;
	game->map_info->map_tmp[y] = NULL;
	close(fd);
}
