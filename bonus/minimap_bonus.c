#include "../includes/cub3d_bonus.h"

void	draw_rectangle(t_info *info, int x, int y, int color)
{
	int i;
	int j;
	int	rec_size;
	int	minimap_size;

	minimap_size = info->conf.win_height / 4;
	rec_size = minimap_size / info->conf.map_col;
	x *= rec_size;
	y *= rec_size;
	i = 0;
	while (i < rec_size && (x + i < info->conf.win_height))
	{
		j = 0;
		while (j < rec_size && (y + j < info->conf.win_width))
		{
			info->buf[x + i][y + j] = color;
			j++;
		}
		i++;
	}
}

void	calc_mininap_object(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->sprite_num)
	{
		draw_rectangle(info, info->sprite[i].y, info->sprite[i].x, 0x00FF00);
		i++;
	}
	draw_rectangle(info, info->posY, info->posX, 0xFF0000);
}

void	calc_minimap(t_info *info)
{
	int		i;
	int		j;
	int		offset_x;

	offset_x = info->conf.win_width / 2;
	i = 0;
	while (i < info->conf.map_row)
	{
		j = 0;
		while (j < info->conf.map_col)
		{
			if (info->conf.map[i][j] == ' ')
				draw_rectangle(info, j, i, 0x00FFFFFF);
			else if (info->conf.map[i][j] == '1')
				draw_rectangle(info, j, i, 0xFFFFFF);
			else
				draw_rectangle(info, j, i, 0x000000);
			j++;
		}
		i++;
	}
	calc_mininap_object(info);
}
