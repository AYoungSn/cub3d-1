#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../mlx/mlx.h"
# include "../bonus/config_bonus.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <unistd.h>

# define Y_PLANE 1
# define X_PLANE 0

# define EVENT_KEY_PRESS	2
# define EVENT_KEY_RELEASE	3
# define EVENT_KEY_EXIT		17

# define KEY_ESC  53
# define KEY_W    13
# define KEY_A    0
# define KEY_S    1
# define KEY_D    2
# define KEY_UP   126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define U_DIV 1
# define V_DIV 1
# define V_MOVE 0.0

typedef struct	s_img
{
	void	    *img_ptr;
	int		    *data;
	int		    size_l;
	int		    bpp;
	int		    endian;
	int		    width;
	int		    height;
}				t_img;

typedef struct  s_key
{
	int			right;
	int			left;
	int			w;
	int			s;
    int         a;
    int         d;
}               t_key;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct  s_info
{
    void        *mlx;
    void        *win;
    double      posX;
    double      posY;
    double      dirX;
    double      dirY;
    double      planeX;
    double      planeY;
    int         score;
    t_img       img;
    int         **buf;
	double		*zBuffer;
    int         sprite_num;
    t_sprite    *sprite;
    int         **texture;
    double      moveSpeed;
    double      rotSpeed;
    t_key       key;
    t_config    conf;
    int         pid;
}               t_info;

typedef struct  s_vetor
{
    double  rayDirX;
    double  rayDirY;
    double  sideDistX;
    double  sideDistY;
    double  deltaDistX;
    double  deltaDistY;
	double  perpWallDist;
    int     mapX;
    int     mapY;
    int     stepX;
    int     stepY;
    int     side;
}               t_vector;

typedef struct  s_back_line
{
    int     lineHeight;
    int     drawStart;
    int     drawEnd;
    int     color;
    double  wallX;
    int     texX;
    int     texY;
    int     texNum;
    double  floorXWall;
    double  floorYWall;
    int     floorTexX;
    int     floorTexY;
}               t_back_line;

typedef struct  s_sprite_line
{
    double  transX;
    double  transY;
	double	x;
	double	y;
    int	    texX;
    int	    texY;
    int     vMoveScreen;
    int     screenX;
    int     height;
    int     width;
    int     drawStartX;
    int     drawEndX;
    int     drawStartY;
    int     drawEndY;
    int     color;
}               t_sprt_line;


typedef struct	s_pair
{
	double		dist;
	int			order;
}				t_pair;

/*
** main_bonus.c
*/

int		main_loop(t_info *info);
int 	main_close(t_info *info);
void    draw(t_info *info);

/*
** info_bonus.c
*/

void    ptr_init(t_info *info);
void	dir_init(t_info *info);
int 	buf_init(t_info *info);
void	key_init(t_info *info);
int 	info_init(t_info *info);

/*
** window_bonus.c
*/

int 	window_init(t_info *info);
void    clear_window(t_info *info);

/*
** close_bonus.c
*/

int		error_exit(t_info *info, char *message, int status);
void	buf_free(t_info *info, int i);
void	clear_game(t_info *info, int status);

/*
** wall1_bonus.c
*/

void    calc_vars(int x, t_vector *vec, t_info *info);
void    calc_dists(t_vector *vec, t_info *info);
void    ray_cast(t_vector *vec, t_info *info);
void    calc_back(t_info *info);

/*
** wall2_bonus.c
*/

void    calc_line(t_back_line *line, t_vector *vec, t_info *info);
void    calc_wall(t_back_line *line, t_vector *vec, t_info *info);
void    coord_wall_tex(int x, t_back_line *line, t_info *info);

/*
** floor_bonus.c
*/

void    calc_floor(t_back_line *line, t_vector *vec);
void    coord_floor_tex(int x, t_back_line *line, t_vector *vec, t_info *info);
void    coord_floor_color(int x, t_back_line *line, t_info *info);

/*
** texture_bonus.c
*/

int     tex_init(t_info *info);
void	load_image(t_info *info, int *texture, char *path, t_img *img);
void    load_texture(t_info *info);
void    tex_free(t_info *info, int i);

/*
** sprite1_bonus.c
*/

int		malloc_sprite(t_info *info);
int 	sprite_init(t_info *info);
void	sort_order(t_pair *sprites, int amount);
void	sort_sprites(int *order, double *dist, int amount);
void    calc_sprite(t_info *info);

/*
** sprite2_bonus.c
*/

void	calc_sprite_pos(t_sprt_line *sprt, int *order, t_info *info, int i);
void	calc_sprite_line(t_sprt_line *sprt, t_info *info);
void	coord_sprite_tex(t_info *info, int *order, t_sprt_line *sprite, int i);

/*
** key_handling_bonus.c
*/

int     key_update(t_info *info);
int     key_press(int key, t_info *info);
int		key_release(int key, t_info *info);

/*
** camera_bonus.c
*/

void    move_vertical(t_info *info, int direction);
void    move_horizontal(t_info *info, int direction);
void    rotate(t_info *info, int direction);

/*
** save_bmp_bonus.c
*/

int		save_image(t_info *info);
int		write_bmp_header(int file, int filesize, t_info *info);

/*
** score_bonus.c
*/

void	draw_score(t_info *info);

/*
** minimap_bonus.c
*/

void	draw_rectangle(t_info *info, int x, int y, int color);
void	calc_mininap_object(t_info *info);
void	calc_minimap(t_info *info);

# endif