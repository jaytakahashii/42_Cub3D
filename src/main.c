#include "cub3D.h"

void	cub_check(char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4))
		error_exit("Must be a .cub file", NULL);
}

/*
** ゲームの初期化
** mlxの初期化
** ウィンドウの作成
** プレイヤーの初期化
*/
void	game_init(t_game *game)
{
	int	x;
	// window_init(game);<---set_imgに移しました。
	// 疑似的な壁
	// draw_line(game, ray_init(vector_init(300, 0), vector_init(0, 1)), 300, MGREEN);
	// draw_line(game, ray_init(vector_init(0, 300), vector_init(1, 0)), 300, MGREEN);
	// draw_line(game, ray_init(vector_init(300, 0), vector_init(-1, 1)), 500, MGREEN);
	x = -1;
	while (++x < (WIN_WIDTH * (WIN_HEIGHT / 2)))
		game->canvas.data[x] = game->map_info->c;
	while (x < WIN_WIDTH * WIN_HEIGHT)
		game->canvas.data[x++] = game->map_info->f;
	draw_player(game, &game->player);
	raycasting(game, &game->player);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas.img, 0, 0);
}

/*
** ゲームのループ
** イベントの受け取り
** 描画
*/
void	game_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_loop(game->mlx);
}

/*
** ゲームの更新
** プレイヤーの移動
** プレイヤーの描画
*/
int	game_update(t_game *game)
{
	int	x;

	x = -1;
	while (++x < (WIN_WIDTH * (WIN_HEIGHT / 2)))
		game->canvas.data[x] = game->map_info->c;
	while (x < WIN_WIDTH * WIN_HEIGHT)
		game->canvas.data[x++] = game->map_info->f;
	x = -1;
	// 疑似的な壁
	// draw_line(game, ray_init(vector_init(300, 0), vector_init(0, 1)), 300, MGREEN);
	// draw_line(game, ray_init(vector_init(0, 300), vector_init(1, 0)), 300, MGREEN);
	// draw_line(game, ray_init(vector_init(300, 0), vector_init(-1, 1)), 500, MGREEN);
	draw_player(game, &game->player);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas.img, 0, 0);
	raycasting(game, &game->player);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game			game;

	game.alloc = NULL;
	if (argc != 2)
		error_exit("Invalid arguments", NULL);
	cub_check(argv);
	map_scan(&game, argv[1]);
	map_check(&game, (&game)->map_info);
	if (set_img(&game))
		error_exit("Failed to set image", NULL);
	game_init(&game);
	game_loop(&game);
	return (0);
}
