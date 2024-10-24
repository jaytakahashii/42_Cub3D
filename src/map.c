#include "cub3D.h"

int	check_map_spell(char **argv)
{
	if (ft_strrchr(argv[1], '.') == 0
		|| ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 4) != 0)
		return (1);
	return (0);
}

int	set_path(char **target, char *map)
{
	pass_space(&map);
	*target = ft_strdup(map);
	return (0);
}

int	set_color(int *target, char *map)
{
	int	i;
	int	*rgb;

	i = -1;
	rgb = (int *)malloc(sizeof(int) * 3);
	if (!rgb)
		return (1);
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
		{
			free(rgb);
			return (1);
		}
	}
	*target = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	free(rgb);
	return (0);
}

int	map_info_init(t_map **map_info, char *argv)
{
	(void)argv; // todo : 使っていない変数を強制的に使う
	// todo : mallocのサイズを変更する
	*map_info = (t_map *)malloc(sizeof(t_map));
	(*map_info)->map = (char **)malloc(sizeof(char *) * OPEN_MAX);
	(*map_info)->map_tmp = (char **)malloc(sizeof(char *) * OPEN_MAX);
	if (!(*map_info)->map || !(*map_info)->map_tmp)
		return (1);
	(*map_info)->map[OPEN_MAX] = NULL;
	(*map_info)->no = NULL;
	(*map_info)->so = NULL;
	(*map_info)->we = NULL;
	(*map_info)->ea = NULL;
	(*map_info)->f = -1;
	(*map_info)->c = -1;
	(*map_info)->p_x = -1;
	(*map_info)->p_y = -1;
	return (0);
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

void	wall_check(char **map, int y, int x, unsigned int *i, int *flag)
{
	*i += 1;
	if (*i > 10000)
	{
		*flag = 1;
		return ;
	}
	if (!map[y] || !map[y][x] || map[y][x] == '1')
		return ;
	else
	{
		map[y][x] = '1';
		if (wall_spell_check(map, y, x))
		{
			*flag = 1;
			return ;
		}
		wall_check(map, y + 1, x, i, flag);
		wall_check(map, y - 1, x, i, flag);
		wall_check(map, y, x + 1, i, flag);
		wall_check(map, y, x - 1, i, flag);
	}
}

int	set_map_info(t_map *map_info, char *map)
{
	if (ft_strncmp(map, "NO", 2) == 0 && ft_isspace(*(map += 2)))
		return (set_path(&map_info->no, map));
	else if (ft_strncmp(map, "SO", 2) == 0 && ft_isspace(*(map += 2)))
		return (set_path(&map_info->so, map));
	else if (ft_strncmp(map, "WE", 2) == 0 && ft_isspace(*(map += 2)))
		return (set_path(&map_info->we, map));
	else if (ft_strncmp(map, "EA", 2) == 0 && ft_isspace(*(map += 2)))
		return (set_path(&map_info->ea, map));
	else if (ft_strncmp(map, "F", 1) == 0 && ft_isspace(*(map += 1)))
		return (set_color(&map_info->f, map));
	else if (ft_strncmp(map, "C", 1) == 0 && ft_isspace(*(map += 1)))
		return (set_color(&map_info->c, map));
	return (2);
}

void	set_player_info(t_map *map_info, char spell, int x, int y)
{
	map_info->p_x = x;
	map_info->p_y = y;
	if (spell == 'N')
	{
		map_info->p_angle = NORTH;
		// todo p_angleという変数に入れられない
		// ft_printf("angle: %f\n", NORTH);
	}
	else if (spell == 'S')
		map_info->p_angle = SOUTH;
	else if (spell == 'W')
		map_info->p_angle = WEST;
	else if (spell == 'E')
		map_info->p_angle = EAST;
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

int	map_spell_check(t_map *map_info, char **map)
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
				if (map_info->p_x != -1)
					return (1);
				set_player_info(map_info, map[y][x], x, y);
			}
			else if (spell_check(map[y][x], 1) == 0)
				return (1);
		}
	}
	if (map_info->p_x == -1)
		return (1);
	return (0);
}

int	map_check(t_map *map_info)
{
	unsigned int	i;
	int				flag;

	i = 0;
	flag = 0;
	if (!map_info->map || !map_info->map[0])
		return (1);
	if (!map_info->no || !map_info->so || !map_info->we || !map_info->ea
		|| map_info->f == -1 || map_info->c == -1)
		return (1);
	if (map_spell_check(map_info, map_info->map))
		return (1);
	wall_check(map_info->map_tmp, map_info->p_y, map_info->p_x, &i, &flag);
	if (flag)
		return (1);
	return (0);
}

int	map_scan(t_game *game, char *argv)
{
	int		y;
	int		fd;
	char	*line;

	y = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1 || map_info_init(&(game->map_info), argv))
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || set_map_info(game->map_info, line) == 0)
		{
			free(line);
			continue ;
		}
		game->map_info->map[y] = ft_strdup(line);
		game->map_info->map_tmp[y] = ft_strdup(line);
		free(line);
		y++;
	}
	game->map_info->map[y] = NULL;
	game->map_info->map_tmp[y] = NULL;
	close(fd);
	return (map_check(game->map_info));
}
