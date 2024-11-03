#include "cub3D.h"

/*
** ウィンドウの初期化
** game: ゲーム構造体
*/
void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	game->canvas.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->canvas.data = (int *)mlx_get_data_addr(game->canvas.img,
			&game->canvas.bpp, &game->canvas.size_line, &game->canvas.endian);
}

/*
** ウィンドウの削除
** game: ゲーム構造体
*/
void	window_exit(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

bool	out_of_window(t_vector pos)
{
	if (pos.x < 0 || pos.x >= WIN_WIDTH || pos.y < 0 || pos.y >= WIN_HEIGHT)
		return (true);
	return (false);
}
