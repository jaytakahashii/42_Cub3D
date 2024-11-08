#include "cub3D.h"

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
				set_player_info(game, map[y][x], vector_init(x, y));
			else if (spell_check(map[y][x], 1) == 0)
				return (1);
		}
	}
	return (0);
}

void	map_check(t_game *game, t_map *map_info)
{
	map_info->flag = 0;
	map_info->flag = 0;
	if (!map_info->map || !map_info->map[0])
		error_exit_free("Map is not found", NULL, game->alloc);
	if (!map_info->no || !map_info->so || !map_info->we || !map_info->ea
		|| map_info->f == -1 || map_info->c == -1)
		error_exit_free("Map information is not found", NULL, game->alloc);
	if (map_spell_check(game, map_info->map))
		error_exit_free("Invalid map", NULL, game->alloc);
	wall_check(map_info, (int)game->player.pos.y / TILE_SIZE,
		(int)game->player.pos.x / TILE_SIZE);
	if (map_info->flag)
		error_exit_free("Invalid map", NULL, game->alloc);
}