/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:28 by kosnakam          #+#    #+#             */
/*   Updated: 2024/12/11 13:05:45 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_open(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error_exit("Failed to open the file", NULL);
	return (fd);
}

void	map_info_init(t_map **map_info, t_allocations **alloc)
{
	int	j;

	int (i) = -1;
	*map_info = (t_map *)malloxit(sizeof(t_map), alloc);
	(*map_info)->map = (char **)malloxit(sizeof(char *) * LINE_MAX, alloc);
	(*map_info)->map_tmp = (char **)malloxit(sizeof(char *) * LINE_MAX, alloc);
	while (++i < LINE_MAX)
	{
		j = -1;
		(*map_info)->map[i] = (char *)malloxit(sizeof(char) * LINE_MAX, alloc);
		while (++j < LINE_MAX)
			(*map_info)->map[i][j] = ' ';
	}
	(*map_info)->map[LINE_MAX] = NULL;
	(*map_info)->map_tmp[LINE_MAX] = NULL;
	(*map_info)->no = NULL;
	(*map_info)->so = NULL;
	(*map_info)->we = NULL;
	(*map_info)->ea = NULL;
	(*map_info)->f = -1;
	(*map_info)->c = -1;
	(*map_info)->count = 0;
	(*map_info)->flag = 0;
	(*map_info)->height = 0;
}

void	copy_map(t_map *map_info, t_allocations **alloc)
{
	int	i;

	i = -1;
	while (++i < LINE_MAX)
		map_info->map_tmp[i] = ft_strdup(map_info->map[i], alloc);
}

void	map_scan(t_game *game, char *argv)
{
	char	*line;

	int (y) = 2;
	int (fd) = ft_open(argv);
	map_info_init(&game->map_info, &(game->alloc));
	read_map_info(fd, game);
	while (1)
	{
		if (y > LINE_MAX)
			error_exit_free("Invalid map", NULL, game->alloc);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || !end_map_info(line))
			error_exit_free("Invalid map", NULL, game->alloc);
		game->map_info->map[y] = ft_memcpy(game->map_info->map[y], line,
				ft_strlen(line));
		free(line);
		y++;
	}
	copy_map(game->map_info, &(game->alloc));
	game->map_info->height = y;
	close(fd);
}
