/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:10:30 by kosnakam          #+#    #+#             */
/*   Updated: 2024/12/06 15:09:24 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	set_color(int *target, char *map)
{
	int	i;
	int	rgb[3];

	i = -1;
	map += 1;
	if (!ft_isspace(*map))
		return (1);
	pass_space(&map);
	while (++i < 3)
	{
		if (!ft_isdigit(*map))
			return (1);
		rgb[i] = ft_atoi(map);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (1);
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
		return (set_color(&map_info->f, map));
	else if (ft_strncmp(map, "C", 1) == 0)
		return (set_color(&map_info->c, map));
	return (1);
}

bool	end_map_info(char *line)
{
	if (!line || *line == '\0')
		return (false);
	pass_space(&line);
	if (*line == '0' || *line == '1')
		return (true);
	return (false);
}

void	read_map_info(int fd, t_game *game)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			error_exit_free("Map is empty", NULL, game->alloc);
		if (end_map_info(line))
		{
			if (ft_strlen(line) > OPEN_MAX)
				error_exit_free("Invalid map", NULL, game->alloc);
			game->map_info->map[1] = ft_memcpy(game->map_info->map[1] + 1,
					line, ft_strlen(line));
			free(line);
			break ;
		}
		set_map_info(game->map_info, line, &(game->alloc));
		free(line);
	}
}
