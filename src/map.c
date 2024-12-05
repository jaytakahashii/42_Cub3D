/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:28 by kosnakam          #+#    #+#             */
/*   Updated: 2024/12/05 15:09:52 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	map_info_init(t_map **map_info, t_allocations **alloc)
{
	*map_info = (t_map *)malloxit(sizeof(t_map), alloc);
	(*map_info)->map = (char **)malloxit(sizeof(char *) * OPEN_MAX, alloc);
	(*map_info)->map_tmp = (char **)malloxit(sizeof(char *) * OPEN_MAX, alloc);
	for (int(i) = 0; i < OPEN_MAX; i++)
	{
		(*map_info)->map[i] = (char *)malloxit(sizeof(char) * OPEN_MAX, alloc);
		(*map_info)->map_tmp[i] = (char *)malloxit(sizeof(char) * OPEN_MAX, alloc);
		for (int(j) = 0; j < OPEN_MAX; j++)
		{
			(*map_info)->map[i][j] = '\0';
			(*map_info)->map_tmp[i][j] = '\0';
		}
	}
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

bool	end_map_info(char *line)
{
	if (!line || *line == '\0')
		return (false);
	pass_space(&line);
	if (*line == '0' || *line == '1')
		return (true);
	return (false);
}

void	map_scan(t_game *game, char *argv)
{
	char *line;

	int(y) = 2;
	int(fd) = ft_open(argv);
	map_info_init(&game->map_info, &(game->alloc));
	read_map_info(fd, game);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			error_exit_free("Map is empty", NULL, game->alloc);
		if (end_map_info(line))
		{
			if (ft_strlen(line) < OPEN_MAX)
			game->map_info->map[1] = ft_memcpy(game->map_info->map[1]+1, line, ft_strlen(line));
			game->map_info->map_tmp[1] = ft_memcpy(game->map_info->map_tmp[1]+1, line, ft_strlen(line));
			free(line);
			break ;
		}
		set_map_info(game->map_info, line, &(game->alloc));
		free(line);
	}
	while (y < OPEN_MAX)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || !end_map_info(line))
			error_exit_free("Invqweralid map", NULL, game->alloc);
		game->map_info->map[y] = ft_memcpy(game->map_info->map[y], line, ft_strlen(line));
		game->map_info->map_tmp[y] = ft_memcpy(game->map_info->map_tmp[y], line, ft_strlen(line));
		free(line);
		y++;
	}
	game->map_info->height = y;
	close(fd);
}
