#include "../includes/cub3d_bonus.h"

void	calc_line(t_back_line *line, t_vector *vec, t_info *info)
{
	if (vec->side == X_PLANE)
	{
		vec->perpWallDist = (vec->mapX - info->posX + (1 - vec->stepX) / 2);
		vec->perpWallDist /= vec->rayDirX;
	}
	else
	{
		vec->perpWallDist = (vec->mapY - info->posY + (1 - vec->stepY) / 2);
		vec->perpWallDist /= vec->rayDirY;
	}
	line->lineHeight = (int)(info->conf.win_height / vec->perpWallDist);
	line->drawStart = -(line->lineHeight) / 2 + info->conf.win_height / 2;
	if (line->drawStart < 0)
		line->drawStart = 0;
	line->drawEnd = line->lineHeight / 2 + info->conf.win_height / 2;
	if (line->drawEnd >= info->conf.win_height)
		line->drawEnd = info->conf.win_height - 1;
}

void	calc_wall(t_back_line *line, t_vector *vec, t_info *info)
{
	if (vec->side == X_PLANE && vec->stepX == 1)
		line->texNum = T_EA;
	else if (vec->side == X_PLANE && vec->stepX == -1)
		line->texNum = T_WE;
	else if (vec->side == Y_PLANE && vec->stepY == 1)
		line->texNum = T_SO;
	else
		line->texNum = T_NO;
	if (vec->side == 0)
		line->wallX = info->posY + vec->perpWallDist * vec->rayDirY;
	else
		line->wallX = info->posX + vec->perpWallDist * vec->rayDirX;
	line->wallX -= floor(line->wallX);
	line->texX = (int)(line->wallX * (double)TEX_WIDTH);
	if (vec->side == 0 && vec->rayDirX > 0)
		line->texX = TEX_WIDTH - line->texX - 1;
	if (vec->side == 1 && vec->rayDirY < 0)
		line->texX = TEX_WIDTH - line->texX - 1;
}

void	coord_wall_tex(int x, t_back_line *line, t_info *info)
{
	double	step;
	double	tex_pos;
	int		tex_tmp;
	int		y;

	step = 1.0 * TEX_HEIGHT / line->lineHeight;
	tex_pos = (line->drawStart - info->conf.win_height
				/ 2 + line->lineHeight / 2) * step;
	y = line->drawStart;
	while (y < line->drawEnd)
	{
		line->texY = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		tex_tmp = TEX_WIDTH * line->texY + line->texX;
		line->color = info->texture[line->texNum][tex_tmp];
		info->buf[y][x] = line->color;
		y++;
	}
}
