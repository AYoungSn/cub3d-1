#include "../includes/cub3d_bonus.h"

void	ptr_init(t_info *info)
{
	info->buf = 0;
	info->texture = 0;
	info->zBuffer = 0;
	info->img.img_ptr = 0;
	info->img.data = 0;
	info->mlx = 0;
	info->win = 0;
	info->sprite = 0;
}

void	dir_init(t_info *info)
{
	if (info->conf.dir == 'N')
	{
		info->dirY = -1;
		info->planeX = 0.66;
	}
	else if (info->conf.dir == 'S')
	{
		info->dirY = 1;
		info->planeX = -0.66;
	}
	else if (info->conf.dir == 'W')
	{
		info->dirX = -1;
		info->planeY = -0.66;
	}
	else
	{
		info->dirX = 1;
		info->planeY = 0.66;
	}
}

int		buf_init(t_info *info)
{
	int i;
	int j;

	info->buf = (int**)malloc(sizeof(int*) * info->conf.win_height);
	if (!(info->buf))
		return (-1);
	i = 0;
	while (i < info->conf.win_height)
	{
		info->buf[i] = (int*)malloc((sizeof(int) * info->conf.win_width));
		if (!(info->buf[i]))
		{
			buf_free(info, i);
			return (-1);
		}
		j = 0;
		while (j < info->conf.win_width)
		{
			info->buf[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

void	key_init(t_info *info)
{
	info->key.right = 0;
	info->key.left = 0;
	info->key.w = 0;
	info->key.s = 0;
	info->key.a = 0;
	info->key.d = 0;
}

int		info_init(t_info *info)
{
	info->posX = info->conf.pos_x + 0.5;
	info->posY = info->conf.pos_y + 0.5;
	info->dirX = 0;
	info->dirY = 0;
	info->planeX = 0;
	info->planeY = 0;
	info->score = 0;
	dir_init(info);
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
	key_init(info);
	if (buf_init(info) == -1 || tex_init(info) == -1)
		return (-1);
	info->zBuffer = (double*)malloc(sizeof(double) * info->conf.win_width);
	return (0);
}
