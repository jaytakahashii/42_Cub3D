#include "cub3D.h"

int	set_img(t_game *game)
{
	window_init(game);
	game->north.img = mlx_xpm_file_to_image(game->mlx, game->map_info->no,
			&game->north.width, &game->north.height);
	game->south.img = mlx_xpm_file_to_image(game->mlx, game->map_info->so,
			&game->south.width, &game->south.height);
	game->west.img = mlx_xpm_file_to_image(game->mlx, game->map_info->we,
			&game->west.width, &game->west.height);
	game->east.img = mlx_xpm_file_to_image(game->mlx, game->map_info->ea,
			&game->east.width, &game->east.height);
	if (!game->north.img || !game->south.img || !game->west.img
		|| !game->east.img)
		return (1);
	game->north.data = (int *)mlx_get_data_addr(game->north.img,
			&game->north.bpp, &game->north.size_line, &game->north.endian);
	game->south.data = (int *)mlx_get_data_addr(game->south.img,
			&game->south.bpp, &game->south.size_line, &game->south.endian);
	game->west.data = (int *)mlx_get_data_addr(game->west.img, &game->west.bpp,
			&game->west.size_line, &game->west.endian);
	game->east.data = (int *)mlx_get_data_addr(game->east.img, &game->east.bpp,
			&game->east.size_line, &game->east.endian);
	if (!game->north.data || !game->south.data || !game->west.data
		|| !game->east.data)
		return (1);
	return (0);
}
