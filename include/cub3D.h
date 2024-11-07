#ifndef CUB3D_H
# define CUB3D_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define ERROR 1

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
# define HALF_TILE_SIZE 32
# define BACKGROUND_SIZE 256

# define M_PI 3.14159265358979323846
# define M_PI_2 1.57079632679489661923
# define M_PI_4 0.78539816339744830962
# define M_PI_3 1.04719755119659774615
# define M_PI_3_2 4.71238898038468985769

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define FOV_ANGLE M_PI_3
# define NUM_RAYS WIN_WIDTH
# define VIEW_DISTANCE WIN_WIDTH
# define MOVE_SPEED 1
# define ROTATE_SPEED 0.008

# define IS_PLAYER 1
# define IS_WALL_OR_EMPTY 2
# define IS_ERROR 0

# define NORTH M_PI_3_2
# define SOUTH M_PI_2
# define WEST M_PI
# define EAST 0

# define MRED 0x00FF0000
# define MGREEN 0x0000FF00
# define MBLUE 0x000000FF
# define MYELLOW 0x00FFFF00
# define MWHITE 0x00FFFFFF
# define MBLACK 0x00000000

# define WALL_EAST 1
# define WALL_NORTH 2
# define WALL_WEST 3
# define WALL_SOUTH 4

typedef struct s_map
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				f;
	int				c;
	char			**map;
	char			**map_tmp;
}					t_map;

typedef struct s_img
{
	struct s_game	*game;
	char			*data;
	void			*img;
	char			*xpm_data;
	void			*xpm_img;
	int				img_width;
	int				img_height;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_ray
{
	t_vector		pos;
	t_vector		dir;
}					t_ray;

typedef struct s_line
{
	double			inclination;
	double			intercept;
}					t_line;

typedef struct line_segment
{
	t_vector		start;
	t_vector		end;
	t_line			line;
}					t_line_segment;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	double		angle;
	double		speed;
	int			up;
	int			back;
	int			left;
	int			right;
	int			turn_left;
	int			turn_right;
}					t_player;

typedef struct s_wall
{
	t_vector		pos;
	double			distance;
	int				color;
	int				x_pos;
}					t_wall;

typedef struct s_line_condition
{
	int				move;
	double			condition;
	bool			is_x_major;
	double			*puls;
}					t_line_condition;

typedef struct s_texture
{
	void			*img;
	int				*data;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_texture;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_player		player;
	t_texture		north;
	t_texture		south;
	t_texture		west;
	t_texture		east;
	t_texture		canvas;
	t_map			*map_info;
	t_img			*img;
	t_allocations	*alloc;
}					t_game;

/* main.c (メイン関数) */

int					game_update(t_game *game);

/* map.c (マップの計算) */

int					check_map_spell(char **argv);
void				map_scan(t_game *game, char *argv);
void				map_check(t_game *game, t_map *map_info);

/* img.c (画像の計算) */
int					set_img(t_game *game);

/* vector.c (ベクトルの計算) */

t_vector			vector_add(t_vector a, t_vector b);
t_vector			vector_sub(t_vector a, t_vector b);
t_vector			vector_mul(t_vector a, double b);
t_vector			vector_div(t_vector a, double b);
t_vector			vector_normalize(t_vector a);
double				vector_len(t_vector a);
double				vector_dot(t_vector a, t_vector b);
double				vector_cross(t_vector a, t_vector b);
t_vector			vector_from_to(t_vector from, t_vector to);
t_vector			vector_rotate(t_vector a, double angle);
t_vector			vector_from_angle(double angle);
t_vector			vector_init(double x, double y);

/* ray.c (レイの計算) */

t_ray				ray_init(t_vector pos, t_vector dir);
t_line				ray_to_line(t_ray ray);
t_line_segment		ray_to_segment(t_ray ray, double length);
t_vector			ray_end(t_ray ray, double length);

/* player.c (プレイヤーの計算) */

t_player			player_init(double x, double y, double angle);
void				draw_player(t_game *game, t_player *player);
int					key_hook(t_game *game);
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);

/* window.c (ウィンドウの計算) */

void				window_init(t_game *game);
int					window_exit(t_game *game);
bool				out_of_window(t_vector pos);

/* draw.c (描画) */

void				draw_line(t_game *game, t_ray ray, double length,
						int color);
void				draw_circle(t_game *game, t_vector point, int radius,
						int color);
// void				draw_rect(t_game *game, t_vector pos, t_vector size,
// 						t_wall wall, t_texture texture);
void				draw_wall(t_game *game, t_wall wall, int ray_num,
						double ray_angle);

/* line.c (直線の計算) */

t_line				line_from_points(t_vector vec1, t_vector vec2);
double				line_calc_y(t_line line, double x);
double				line_calc_x(t_line line, double y);

/* segment.c (線分の計算) */

t_line_segment		line_segment_init(t_vector start, t_vector end);
t_vector			line_intersection(t_line_segment line1,
						t_line_segment line2);

/* raycasting.c (レイキャスティング) */

void				raycasting(t_game *game, t_player *player);

/* dda.c (DDAアルゴリズム) */

t_wall				dda_up(t_game *game, t_line_segment ray);
t_wall				dda_down(t_game *game, t_line_segment ray);
t_wall				dda_left(t_game *game, t_line_segment ray);
t_wall				dda_right(t_game *game, t_line_segment ray);

#endif
