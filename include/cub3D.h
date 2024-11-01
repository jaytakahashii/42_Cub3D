#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# include "mlx.h"

# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# ifdef __APPLE__
// key code for mac
#  define ESC 53
#  define UP 13
#  define DOWN 1
#  define LEFT 0
#  define RIGHT 2
#  define UP_ARROW 126
#  define DOWN_ARROW 125
#  define LEFT_ARROW 123
#  define RIGHT_ARROW 124
#  define DESTROYNOTIFY 17
// 1L << 17
#  define STRUCTURENOTIFYMASK 131072
# endif

# ifdef __linux__
// include for linux miniLibX
#  include <X11/X.h>
#  include <X11/keysym.h>
// key code for linux
#  define ESC 65307
#  define UP 119
#  define DOWN 115
#  define LEFT 97
#  define RIGHT 100
#  define UP_ARROW 65362
#  define DOWN_ARROW 65364
#  define LEFT_ARROW 65361
#  define RIGHT_ARROW 65363
#  define DESTROYNOTIFY DestroyNotify
#  define STRUCTURENOTIFYMASK StructureNotifyMask
# endif

# define TILE_SIZE 64
# define BACKGROUND_SIZE 256

# define M_PI 3.14159265358979323846
# define M_PI_2 1.57079632679489661923

# define WIN_WIDTH 2048
# define WIN_HEIGHT 1024

# define FOV_ANGLE M_PI * 2
# define FOV_ANGLE_HALF FOV_ANGLE / 2
# define NUM_RAYS WIN_WIDTH / 2
// # define NUM_RAYS 5
# define VIEW_DISTANCE WIN_WIDTH > WIN_HEIGHT ? WIN_WIDTH : WIN_HEIGHT

# define NORTH 3 * M_PI / 2
# define SOUTH M_PI / 2
# define WEST M_PI
# define EAST 0

# define MRED 0x00FF0000
# define MGREEN 0x0000FF00
# define MBLUE 0x000000FF
# define MWHITE 0x00FFFFFF
# define MBLACK 0x00000000

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	int		p_x;
	int		p_y;
	double		p_angle;
	char	**map;
	char	**map_tmp;
}	t_map;

typedef struct s_img
{
	struct s_game	*game;
	char	*data;
	void	*img;
	char	*xpm_data;
	void	*xpm_img;
	int		img_width;
	int		img_height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_ray
{
	t_vector	pos;
	t_vector	dir;
}	t_ray;

typedef struct s_line
{
	double	inclination;
	double	intercept;
}	t_line;

typedef struct line_segment
{
	t_vector	start;
	t_vector	end;
	t_line		line;
}	t_line_segment;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	double		angle; // radian
	double		speed;
	int			up;
	int			back;
	int			left;
	int			right;
	int		turn_left;
	int		turn_right;
}	t_player;

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_texture	canvas;
	t_map		*map_info;
	t_img		*img;
}	t_game;

/* main.c (メイン関数) */

int				game_update(t_game *game);

/* map.c (マップの計算) */

int				check_map_spell(char **argv);
int				map_scan(t_game *game, char *argv);

/* img.c (画像の計算) */
int				set_img(t_game *game);

/* vector.c (ベクトルの計算) */

t_vector		vector_add(t_vector a, t_vector b);
t_vector		vector_sub(t_vector a, t_vector b);
t_vector		vector_mul(t_vector a, double b);
t_vector		vector_div(t_vector a, double b);
t_vector		vector_normalize(t_vector a);
double			vector_len(t_vector a);
double			vector_dot(t_vector a, t_vector b);
double			vector_cross(t_vector a, t_vector b);
t_vector		vector_from_to(t_vector from, t_vector to);
t_vector		vector_reflect(t_vector a, t_vector normal);
t_vector		vector_project(t_vector a, t_vector b);
t_vector		vector_rotate(t_vector a, double angle);
t_vector		vector_from_angle(double angle);
t_vector		vector_init(double x, double y);

/* ray.c (レイの計算) */

t_ray			ray_init(t_vector pos, t_vector dir);
t_line			ray_to_line(t_ray ray);
t_line_segment	ray_to_segment(t_ray ray, double length);

/* player.c (プレイヤーの計算) */

t_player		player_init(double x, double y, double angle, double speed);
void			draw_player(t_game *game, t_player *player);
int				key_hook(t_game *game);
// int		key_hook(int keycode, t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);

/* window.c (ウィンドウの計算) */

void			window_init(t_game *game);
int			window_exit(t_game *game);
void			mlx_line_put(t_game *game, t_ray ray, double length, int color);
void			draw_circle(t_game *game, t_vector point, int radius, int color);
void			draw_rect(t_game *game, t_vector pos, t_vector size, int color, int y);

/* line.c (直線の計算) */

t_line			line_from_points(t_vector vec1, t_vector vec2);
double			line_calc_y(t_line line, double x);
double			line_calc_x(t_line line, double y);

/* segment.c (線分の計算) */

t_line_segment	line_segment_init(t_vector start, t_vector end);
t_vector		line_intersection(t_line_segment line1, t_line_segment line2);

/* raycasting.c (レイキャスティング) */

void			raycasting(t_game *game, t_player *player);
void			draw_wall(t_game *game, int num, double angle, double distance, int y);

#endif
