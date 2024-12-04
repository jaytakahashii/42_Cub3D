#include "cub3D.h"

int	check_map_spell(char **argv)
{
	if (ft_strrchr(argv[1], '.') == 0
		|| ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 4) != 0)
		return (1);
	return (0);
}

int	set_path(char **target, char *map, t_allocations **alloc)
{
	int	i;

	i = 0;
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
	rgb = (int *)malloxit(sizeof(int) * 3, alloc);
	while (*map == 32 || (*map >= 9 && *map <= 13))
		map++;
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

int	set_map_info(t_map *map_info, char *map, t_allocations **alloc)
{
	if (ft_strncmp(map, "NO", 2) == 0 && ft_isspace(*(map += 2)))
		return (set_path(&map_info->no, map, alloc));
	else if (ft_strncmp(map, "SO", 2) == 0 && ft_isspace(*(map += 2)))
		return (set_path(&map_info->so, map, alloc));
	else if (ft_strncmp(map, "WE", 2) == 0 && ft_isspace(*(map += 2)))
		return (set_path(&map_info->we, map, alloc));
	else if (ft_strncmp(map, "EA", 2) == 0 && ft_isspace(*(map += 2)))
		return (set_path(&map_info->ea, map, alloc));
	else if (ft_strncmp(map, "F", 1) == 0 && ft_isspace(*(map += 1)))
		return (set_color(&map_info->f, map, alloc));
	else if (ft_strncmp(map, "C", 1) == 0 && ft_isspace(*(map += 1)))
		return (set_color(&map_info->c, map, alloc));
	return (2);
}

void	set_player_info(t_game *game, char spell, t_vector p_pos)
{
	double	p_angle;

	p_angle = 0;
	if (spell == 'N')
		p_angle = NORTH;
	else if (spell == 'S')
		p_angle = SOUTH;
	else if (spell == 'W')
		p_angle = WEST;
	else if (spell == 'E')
		p_angle = EAST;
	game->player = player_init(p_pos.x * TILE_SIZE + TILE_SIZE / 2,
			p_pos.y * TILE_SIZE + TILE_SIZE / 2, p_angle);
}

int	spell_check(char spell, int mode)
{
	if (mode == 1)
	{
		if (spell == '0' || spell == '1' || spell == '\n'
			|| spell == ' ' || spell == 'N' || spell == 'S'
			|| spell == 'W' || spell == 'E')
		{
			if (spell == 'N' || spell == 'S'
				|| spell == 'W' || spell == 'E')
				return (1);
			return (2);
		}
	}
	return (0);
}

int	map_spell_check(t_game *game, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y] && map[y][++x])
		{
			if (spell_check(map[y][x], 1) == 1)
			{
				set_player_info(game, map[y][x], vector_init(x, y));
			}
			else if (spell_check(map[y][x], 1) == 0)
				return (1);
		}
	}
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

void	map_check(t_game *game, t_map *map_info)
{
	int				flag;
	unsigned int	count;

	flag = 0;
	count = 0;
	if (!map_info->map || !map_info->map[0])
		error_exit_free("Map is not found", NULL, game->alloc);
	if (!map_info->no || !map_info->so || !map_info->we || !map_info->ea
		|| map_info->f == -1 || map_info->c == -1)
		error_exit_free("Map information is not found", NULL, game->alloc);
	if (map_spell_check(game, map_info->map))
		error_exit_free("Invalid map", NULL, game->alloc);
	wall_check(map_info->map_tmp, (int)game->player.pos.y / TILE_SIZE,
		(int)game->player.pos.x / TILE_SIZE, &count, &flag);
	if (flag)
		error_exit_free("Invalid map", NULL, game->alloc);
}

int	ft_open(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error_exit("Failed to open the file", NULL);
	return (fd);
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
