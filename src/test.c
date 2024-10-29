// #include <mlx.h>
// #include <stdio.h>

// #define BG_COLOR 0x02A630  // 背景の緑色

// // 画像を引き伸ばして表示する関数
// void render_stretched_image_with_xpm(void *mlx_ptr, void *win_ptr, char *xpm_file)
// {
//     int win_width = 800;
//     int win_height = 600;
//     int img_width, img_height;
//     void *bg_img_ptr;
//     void *xpm_img_ptr;
//     char *bg_img_data;
//     char *xpm_img_data;
//     int bpp, size_line, endian;
//     int x, y;

//     // 背景用の画像を作成（800x600）
//     bg_img_ptr = mlx_new_image(mlx_ptr, win_width, win_height);
//     bg_img_data = mlx_get_data_addr(bg_img_ptr, &bpp, &size_line, &endian);

//     // 背景画像を緑色で塗りつぶす
//     for (y = 0; y < win_height; y++)
//     {
//         for (x = 0; x < win_width; x++)
//         {
//             *(int *)(bg_img_data + (y * size_line + x * (bpp / 8))) = BG_COLOR;
//         }
//     }

//     // XPM画像を読み込む
//     xpm_img_ptr = mlx_xpm_file_to_image(mlx_ptr, xpm_file, &img_width, &img_height);
//     if (!xpm_img_ptr)
//     {
//         printf("Failed to load XPM file: %s\n", xpm_file);
//         return;
//     }
// 	int bpp_xpm, size_line_xpm, endian_xpm;
//     xpm_img_data = mlx_get_data_addr(xpm_img_ptr, &bpp_xpm, &size_line_xpm, &endian_xpm);

//     // 引き伸ばしの倍率を計算
//     // double scale_x = (double)win_width / img_width;
//     // double scale_y = (double)win_height / img_height;

//     // 背景上にXPM画像を引き伸ばして描画（バックバッファに合成）
//     for (y = 0; y < img_height; y++)
//     {
//         for (x = 0; x < img_width; x++)
//         {
//             // 元の画像の座標に対応するピクセルを計算（最近傍補間）
//             // int src_x = (int)(x / scale_x);
//             // int src_y = (int)(y / scale_y);

//             // 元の画像のピクセルを取得して拡大後の位置に配置
// 			printf("%d\n", y * size_line_xpm + x * (bpp_xpm / 8));
//             int color = *(int *)(xpm_img_data + (y * size_line_xpm + x * (bpp_xpm / 8)));
//             *(int *)(bg_img_data + (y * size_line + x * (bpp / 8))) = color;
//         }
//     }
//     // 背景画像と引き伸ばされたXPM画像を一度だけウィンドウに表示
//     mlx_put_image_to_window(mlx_ptr, win_ptr, bg_img_ptr, 0, 0);
// }

// int main(void)
// {
//     void *mlx_ptr;
//     void *win_ptr;

//     // MiniLibX 初期化
//     mlx_ptr = mlx_init();
//     if (!mlx_ptr)
//     {
//         printf("Failed to initialize MiniLibX\n");
//         return 1;
//     }
//     // ウィンドウの作成（幅800、高さ600）
//     win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Stretched XPM Image");

//     // 背景に緑色を塗りつぶし、XPM画像を引き伸ばして一度だけ表示
//     render_stretched_image_with_xpm(mlx_ptr, win_ptr, "./img/eagle.xpm");

//     // イベントループ
//     mlx_loop(mlx_ptr);

//     return 0;
// }
