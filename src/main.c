#include "cub3D.h"

int cub_check(char **argv)
{
	if (ft_strrchr(argv[1], '.') == 0
		|| ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 4) != 0)
		return (1);
	return (0);
}

/*
** ゲームの初期化
** mlxの初期化
** ウィンドウの作成
** プレイヤーの初期化
*/
void	game_init(t_game *game)
{
	// window_init(game);<---set_imgに移しました。
	game->player = player_init(200, 250, NORTH, 1);
	game->player.up = 0;
	game->player.back = 0;
	game->player.left = 0;
	game->player.right = 0;
	game->player.turn_left = 0;
	game->player.turn_right = 0;
	// 疑似的な壁
	mlx_line_put(game, ray_init(vector_init(300, 0), vector_init(0, 1)), 300, MGREEN);
	mlx_line_put(game, ray_init(vector_init(0, 300), vector_init(1, 0)), 300, MGREEN);
	mlx_line_put(game, ray_init(vector_init(300, 0), vector_init(-1, 1)), 500, MGREEN);
	draw_player(game, &game->player);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas.img, 0, 0);
	raycasting(game, &game->player);
}

/*
** ゲームのループ
** イベントの受け取り
** 描画
*/
void	game_loop(t_game *game)
{
	mlx_hook(game->win, 17, 0, window_exit, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_loop_hook(game->mlx, key_hook, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
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
	// mlx_clear_window(game->mlx, game->win);
	while (++x < WIN_WIDTH * WIN_HEIGHT)
		game->canvas.data[x] = 0;
	x = -1;
	// 疑似的な壁
	mlx_line_put(game, ray_init(vector_init(300, 0), vector_init(0, 1)), 300, MGREEN);
	mlx_line_put(game, ray_init(vector_init(0, 300), vector_init(1, 0)), 300, MGREEN);
	mlx_line_put(game, ray_init(vector_init(300, 0), vector_init(-1, 1)), 500, MGREEN);
	draw_player(game, &game->player);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas.img, 0, 0);
	raycasting(game, &game->player);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || cub_check(argv) || map_scan(&game, argv[1]) || set_img(&game))
		exit(0);
	game_init(&game);
	game_loop(&game);
	return (0);
}
