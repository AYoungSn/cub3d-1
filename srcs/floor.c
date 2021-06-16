#include "../includes/cub3d.h"

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

void	coord_floor_color(int x, t_back_line *line, t_info *info)
{
	int		y;

	if (line->drawEnd < 0)
		line->drawEnd = info->conf.win_height;
	y = line->drawEnd + 1;
	while (y < info->conf.win_height)
	{
		info->buf[y][x] = info->conf.cf_color[1];
		info->buf[info->conf.win_height - y - 1][x] = info->conf.cf_color[0];
		y++;
	}
}
