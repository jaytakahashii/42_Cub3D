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
	*map_info = (t_map *)malloxit(sizeof(t_map), alloc);
	(*map_info)->map = (char **)malloxit(sizeof(char *) * MAP_MAX + 2, alloc);
	(*map_info)->map_tmp = (char **)malloxit(sizeof(char *) * MAP_MAX + 2, alloc);
	for (int(i) = 0; i < MAP_MAX + 2; i++)
	{
		(*map_info)->map[i] = (char *)malloxit(sizeof(char) * MAP_MAX + 2, alloc);
		(*map_info)->map_tmp[i] = (char *)malloxit(sizeof(char) * MAP_MAX + 2, alloc);
		for (int(j) = 0; j < MAP_MAX + 2; j++)
		{
			(*map_info)->map[i][j] = '\0';
			(*map_info)->map_tmp[i][j] = '\0';
		}
	}
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

void	*ft_cub_memcpy(void *dst, const void *src, size_t n)
{
	size_t		index;
	char		*dst_byte;
	const char	*src_byte;

	if (!dst && !src)
		return (NULL);
	dst_byte = (char *)dst;
	src_byte = (const char *)src;
	index = 0;
	while (index < n)
	{
		dst_byte[index + 1] = src_byte[index];
		index++;
	}
	return (dst);
}


void	map_scan(t_game *game, char *argv)
{
	char	*line;
	int		i;

	i = 0;
	int(fd) = ft_open(argv);
	map_info_init(&game->map_info, &(game->alloc));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			error_exit_free("Map is empty", NULL, game->alloc);
		if (end_map_info(line))
		{
			if (ft_strlen(line) > MAP_MAX)
				error_exit_free("Invalid map", NULL, game->alloc);
			game->map_info->map[i + 1] = ft_cub_memcpy(game->map_info->map[i + 1], line, ft_strlen(line));
			game->map_info->map_tmp[i + 1] = ft_cub_memcpy(game->map_info->map_tmp[i + 1], line, ft_strlen(line));
			free(line);
			break ;
		}
		set_map_info(game->map_info, line, &(game->alloc));
		free(line);
	}
	i++;
	while (i <= MAP_MAX)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || !end_map_info(line))
			error_exit_free("Invqweralid map", NULL, game->alloc);
		if (ft_strlen(line) > MAP_MAX)
			error_exit_free("Invalid map", NULL, game->alloc);
		game->map_info->map[i + 1] = ft_cub_memcpy(game->map_info->map[i + 1], line, ft_strlen(line));
		game->map_info->map_tmp[i + 1] = ft_cub_memcpy(game->map_info->map_tmp[i + 1], line, ft_strlen(line));
		free(line);
		i++;
	}
	close(fd);
}
