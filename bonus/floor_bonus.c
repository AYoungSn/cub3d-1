#include "../includes/cub3d_bonus.h"

void	calc_floor(t_back_line *line, t_vector *vec)
{
	if (vec->side == X_PLANE && vec->rayDirX > 0)
	{
		line->floorXWall = vec->mapX;
		line->floorYWall = vec->mapY + line->wallX;
	}
	else if (vec->side == X_PLANE && vec->rayDirX < 0)
	{
		line->floorXWall = vec->mapX + 1.0;
		line->floorYWall = vec->mapY + line->wallX;
	}
	else if (vec->side == Y_PLANE && vec->rayDirY > 0)
	{
		line->floorXWall = vec->mapX + line->wallX;
		line->floorYWall = vec->mapY;
	}
	else
	{
		line->floorXWall = vec->mapX + line->wallX;
		line->floorYWall = vec->mapY + 1.0;
	}
}

void	coord_floor_tex(int x, t_back_line *line, t_vector *vec, t_info *info)
{
	int		y;
	int		tex_tmp;
	double	weight;

	if (info->conf.tex_path[T_F] == 0 && info->conf.tex_path[T_C] == 0)
		return ;
	if (line->drawEnd < 0)
		line->drawEnd = info->conf.win_height;
	y = line->drawEnd + 1;
	while (y < info->conf.win_height)
	{
		weight = (info->conf.win_height / (2.0 * y - info->conf.win_height))
				/ vec->perpWallDist;
		line->floorTexX = (int)((weight * line->floorXWall + (1.0 - weight)
							* info->posX) * TEX_WIDTH) % TEX_WIDTH;
		line->floorTexY = (int)((weight * line->floorYWall + (1.0 - weight)
							* info->posY) * TEX_HEIGHT) % TEX_HEIGHT;
		tex_tmp = TEX_WIDTH * line->floorTexY + line->floorTexX;
		if (info->conf.tex_path[T_F] != 0)
			info->buf[y][x] = info->texture[T_F][tex_tmp];
		if (info->conf.tex_path[T_C] != 0)
			info->buf[info->conf.win_height
			- y][x] = info->texture[T_C][tex_tmp];
		y++;
	}
}

void	coord_floor_color(int x, t_back_line *line, t_info *info)
{
	int		y;

	if (info->conf.cf_color[0] == -1 && info->conf.cf_color[1] == -1)
		return ;
	if (line->drawEnd < 0)
		line->drawEnd = info->conf.win_height;
	y = line->drawEnd + 1;
	while (y < info->conf.win_height)
	{
		if (info->conf.cf_color[1] != -1)
			info->buf[y][x] = info->conf.cf_color[1];
		if (info->conf.cf_color[0] != -1)
			info->buf[info->conf.win_height - y
			- 1][x] = info->conf.cf_color[0];
		y++;
	}
}
