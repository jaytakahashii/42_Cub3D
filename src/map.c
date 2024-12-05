/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:28 by kosnakam          #+#    #+#             */
/*   Updated: 2024/12/05 14:24:14 by kosnakam         ###   ########.fr       */
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

void	map_scan(t_game *game, char *argv)
{
	char	*line;

	int (i) = 1;
	int (fd) = ft_open(argv);
	map_info_init(&game->map_info, &(game->alloc));
	read_map_info(fd, game);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || !end_map_info(line))
			error_exit_free("Invalid map", NULL, game->alloc);
		game->map_info->map[i] = ft_strdup(line, &(game->alloc));
		game->map_info->map_tmp[i] = ft_strdup(line, &(game->alloc));
		free(line);
		i++;
	}
	game->map_info->height = i;
	close(fd);
}
