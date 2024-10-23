#include <mlx.h>
#include <stdio.h>
#include <math.h>

#define BG_COLOR 0x02A630  // 背景の緑色
#define SHEAR_FACTOR 0.5   // シアー変換の係数（平行四辺形の傾き）

// 画像を平行四辺形に変形してウィンドウに表示する関数
void render_sheared_image_with_xpm(void *mlx_ptr, void *win_ptr, char *xpm_file)
{
    int win_width = 800;
    int win_height = 600;
    int img_width, img_height;
    void *bg_img_ptr;
    void *xpm_img_ptr;
    char *bg_img_data;
    char *xpm_img_data;
    int bpp, size_line, endian;
    int x, y;

    // 背景用の画像を作成（800x600）
    bg_img_ptr = mlx_new_image(mlx_ptr, win_width, win_height);
    bg_img_data = mlx_get_data_addr(bg_img_ptr, &bpp, &size_line, &endian);

    // 背景画像を緑色で塗りつぶす
    for (y = 0; y < win_height; y++)
    {
        for (x = 0; x < win_width; x++)
        {
            *(int *)(bg_img_data + (y * size_line + x * (bpp / 8))) = BG_COLOR;
        }
    }

    // XPM画像を読み込む
    xpm_img_ptr = mlx_xpm_file_to_image(mlx_ptr, xpm_file, &img_width, &img_height);
    if (!xpm_img_ptr)
    {
        printf("Failed to load XPM file: %s\n", xpm_file);
        return;
    }
	int bpp_xpm, size_line_xpm, endian_xpm;
    xpm_img_data = mlx_get_data_addr(xpm_img_ptr, &bpp_xpm, &size_line_xpm, &endian_xpm);

    // 平行四辺形にするための座標変換
    int offset_x = (win_width - img_width) / 2;
    int offset_y = (win_height - img_height) / 2;

    for (y = 0; y < img_height; y++)
    {
        for (x = 0; x < img_width; x++)
        {
            int color = *(int *)(xpm_img_data + (y * size_line_xpm + x * (bpp_xpm / 8)));

            // シアー変換を使って座標を変換（平行四辺形に変形）
            int new_x = x + y * SHEAR_FACTOR;
            int new_y = y;

            // 新しい座標がウィンドウ内に収まるか確認
            if (new_x + offset_x >= 0 && new_x + offset_x < win_width &&
                new_y + offset_y >= 0 && new_y + offset_y < win_height)
            {
                // 変形後の画像を背景に描画
                *(int *)(bg_img_data + ((new_y + offset_y) * size_line + (new_x + offset_x) * (bpp / 8))) = color;
            }
        }
    }

    // 最後に背景画像をウィンドウに一度だけ表示
    mlx_put_image_to_window(mlx_ptr, win_ptr, bg_img_ptr, 0, 0);
}

int main(void)
{
    void *mlx_ptr;
    void *win_ptr;

    // MiniLibX 初期化
    mlx_ptr = mlx_init();
    if (!mlx_ptr)
    {
        printf("Failed to initialize MiniLibX\n");
        return 1;
    }

    // ウィンドウの作成（幅800、高さ600）
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Sheared XPM Image");

    // 背景に緑色を塗りつぶして平行四辺形に変形されたXPM画像を貼り付け
    render_sheared_image_with_xpm(mlx_ptr, win_ptr, "./img/eagle.xpm");

    // イベントループ
    mlx_loop(mlx_ptr);

    return 0;
}
// // 	 return 0;
// // }

// // int main(void)
// // {
// // 	 void *mlx_ptr;
// // 	 void *win_ptr;
// // 	 void *img_ptr;
// // 	 int img_width, img_height;

// // 	 // MiniLibX 初期化
// // 	 mlx_ptr = mlx_init();
// // 	 win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Rotated Image");

// // 	 // 画像の読み込み
// // 	 img_ptr = mlx_xpm_file_to_image(mlx_ptr, "./img/eagle.xpm", &img_width, &img_height);

// // 	 // 画像の回転
// // 	 rotate_image(mlx_ptr, win_ptr, img_ptr, img_width, img_height);

// // 	 // イベントループ
// // 	 mlx_loop(mlx_ptr);

// // 	 return 0;
// // }


// #define BG_COLOR 0x02A630  // 背景の緑色

// // 画像の背景を緑色で塗りつぶし、XPM画像を貼り付ける関数
// void render_image_with_xpm(void *mlx_ptr, void *win_ptr, char *xpm_file)
// {
// 	int win_width = 800;
// 	int win_height = 600;
// 	int img_width = 64, img_height = 64;
// 	void *bg_img_ptr;
// 	void *xpm_img_ptr;
// 	char *bg_img_data;
// 	int bpp, size_line, endian;
// 	int x, y;

// 	// 背景用の画像を作成（800x600）
// 	bg_img_ptr = mlx_new_image(mlx_ptr, win_width, win_height);
// 	bg_img_data = mlx_get_data_addr(bg_img_ptr, &bpp, &size_line, &endian);

// 	// 背景画像を緑色で塗りつぶす
// 	for (y = 0; y < win_height; y++)
// 	{
// 		for (x = 0; x < win_width; x++)
// 		{
// 			*(int *)(bg_img_data + (y * size_line + x * (bpp / 8))) = BG_COLOR;
// 		}
// 	}

// 	// XPM画像を読み込む
// 	xpm_img_ptr = mlx_xpm_file_to_image(mlx_ptr, xpm_file, &img_width, &img_height);
// 	if (!xpm_img_ptr)
// 	{
// 		ft_printf("Failed to load XPM file: %s\n", xpm_file);
// 		return;
// 	}

// 	// XPM画像を背景画像に貼り付ける
// 	char *xpm_img_data = mlx_get_data_addr(xpm_img_ptr, &bpp, &size_line, &endian);

// 	// XPM画像の座標を設定（中央に配置）
// 	// int offset_x = (win_width - img_width) / 2;
// 	// int offset_y = (win_height - img_height) / 2;

// 	// XPM画像を背景にコピー
// 	for (y = 0; y < img_height; y++)
// 	{
// 		for (x = 0; x < img_width; x++)
// 		{
// 			unsigned int color = *(int *)(xpm_img_data + (y * size_line + x * (bpp / 8)));
// 			if (color != 0xFF000000)  // 透明色を無視（XPMの透明色が黒ならここで判定）
// 			{
// 				*(int *)(bg_img_data + (y * size_line + x * (bpp / 8))) = color;
// 			}
// 		}
// 	}
// 	// 最後に背景画像をウィンドウに一度だけ表示
// 	mlx_put_image_to_window(mlx_ptr, win_ptr, bg_img_ptr, 0, 0);
// }

// int main(void)
// {
// 	void *mlx_ptr;
// 	void *win_ptr;

// 	// MiniLibX 初期化
// 	mlx_ptr = mlx_init();
// 	if (!mlx_ptr)
// 	{
// 		ft_printf("Failed to initialize MiniLibX\n");
// 		return 1;
// 	}

// 	// ウィンドウの作成（幅800、高さ600）
// 	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Green Background with XPM Image");

// 	// 背景に緑色を塗りつぶしてXPM画像を貼り付け
// 	render_image_with_xpm(mlx_ptr, win_ptr, "./img/eagle.xpm");

// 	// イベントループ
// 	mlx_loop(mlx_ptr);

// 	return 0;
// }