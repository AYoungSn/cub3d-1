#include "../includes/cub3d.h"

void	move_vertical(t_info *info, int direction)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = info->posX + direction * info->dirX * info->moveSpeed;
	tmp_y = info->posY + direction * info->dirY * info->moveSpeed;
	if (direction == 1)
	{
		if (info->conf.map[tmp_x][(int)info->posY] != '1')
			info->posX += info->dirX * info->moveSpeed;
		if (info->conf.map[(int)info->posX][tmp_y] != '1')
			info->posY += info->dirY * info->moveSpeed;
	}
	if (direction == -1)
	{
		if (info->conf.map[tmp_x][(int)info->posY] != '1')
			info->posX -= info->dirX * info->moveSpeed;
		if (info->conf.map[(int)info->posX][tmp_y] != '1')
			info->posY -= info->dirY * info->moveSpeed;
	}
}

void	move_horizontal(t_info *info, int direction)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = info->posX + direction * info->planeX * info->moveSpeed;
	tmp_y = info->posY + direction * info->planeY * info->moveSpeed;
	if (direction == 1)
	{
		if (info->conf.map[tmp_x][tmp_y] != '1')
		{
			info->posX += info->planeX * info->moveSpeed;
			info->posY += info->planeY * info->moveSpeed;
		}
	}
	if (direction == -1)
	{
		if (info->conf.map[tmp_x][tmp_y] != '1')
		{
			info->posX -= info->planeX * info->moveSpeed;
			info->posY -= info->planeY * info->moveSpeed;
		}
	}
}

void	rotate(t_info *info, int direction)
{
	double	old_dir_x;
	double	old_pln_x;
	double	tmp_x;
	double	tmp_y;

	old_dir_x = info->dirX;
	tmp_x = info->dirX * cos(direction * info->rotSpeed);
	tmp_y = info->dirY * sin(direction * info->rotSpeed);
	info->dirX = tmp_x - tmp_y;
	tmp_x = old_dir_x * sin(direction * info->rotSpeed);
	tmp_y = info->dirY * cos(direction * info->rotSpeed);
	info->dirY = tmp_x + tmp_y;
	old_pln_x = info->planeX;
	tmp_x = info->planeX * cos(direction * info->rotSpeed);
	tmp_y = info->planeY * sin(direction * info->rotSpeed);
	info->planeX = tmp_x - tmp_y;
	tmp_x = old_pln_x * sin(direction * info->rotSpeed);
	tmp_y = info->planeY * cos(direction * info->rotSpeed);
	info->planeY = tmp_x + tmp_y;
}