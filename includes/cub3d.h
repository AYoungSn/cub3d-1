/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:58:49 by sunhkim           #+#    #+#             */
/*   Updated: 2021/03/27 15:59:37 by sunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

# define NS 1
# define EW 0

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

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

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
	int			a;
	int			w;
	int			s;
	int			d;
}               t_key;


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
    t_img       img;
    int         map[MAP_HEIGHT][MAP_WIDTH];
    int         buf[WIN_HEIGHT][WIN_WIDTH];
	double		zBuffer[WIN_WIDTH];
    int         **texture;
    double      moveSpeed;
    double      rotSpeed;
    t_key       key;
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

typedef struct  s_line
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
}               t_line;

/*
** main.c
*/

int		main_loop(t_info *info);
int 	main_close(t_info *info);
void    error_exit(char *message);
void    draw(t_info *info);

/*
** init.c
*/

int 	window_init(t_info *info);
void	info_init(t_info *info);
void	key_init(t_info *info);
int     tex_init(t_info *info);
void	game_init(t_info *info);

/*
** close.c
*/

void    tex_free(t_info *info, int i);

/*
** wall1.c
*/

void    calc_vars(int x, t_vector *vec, t_info *info);
void    calc_dists(t_vector *vec, t_info *info);
void    ray_cast(t_vector *vec, t_info *info);
void    calc_back(t_info *info);

/*
** wall2.c
*/

void    calc_line(t_line *line, t_vector *vec, t_info *info);
void    calc_wall(t_line *line, t_vector *vec, t_info *info);
void    coord_wall_texture(int x, t_line *line, t_vector *vec, t_info *info);

/*
** floor.c
*/

void    calc_floor(t_line *line, t_vector *vec);
int     calc_pattern(double weight, t_line *line, t_info *info);
void    coord_floor_texture(int x, t_line *line, t_vector *vec, t_info *info);

/*
** texture.c
*/

void	load_image(t_info *info, int *texture, char *path, t_img *img);
void    load_texture(t_info *info);

/*
** sprite.c
*/

void    calc_sprite(t_info *info);

/*
** key_handling.c
*/

void    move(t_info *info, int direction);
void    rotate(t_info *info, int direction);
int     key_update(t_info *info);
int     key_press(int key, t_info *info);
int		key_release(int key, t_info *info);

# endif
