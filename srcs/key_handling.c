#include "../includes/cub3d.h"

void	move(t_info *info, int direction)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = info->posX + direction * info->dirX * info->moveSpeed;
	tmp_y = info->posY + direction * info->dirY * info->moveSpeed;
	if (direction == 1)
	{
		if (!info->map[tmp_x][tmp_y])
		{
			info->posX += info->dirX * info->moveSpeed;
			info->posY += info->dirY * info->moveSpeed;
		}
	}
	if (direction == -1)
	{
		if (!info->map[tmp_x][tmp_y])
		{
			info->posX -= info->dirX * info->moveSpeed;
			info->posY -= info->dirY * info->moveSpeed;
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

int		key_update(t_info *info)
{
	if (info->key.w)
		move(info, 1);
	if (info->key.s)
		move(info, -1);
	if (info->key.d)
		rotate(info, -1);
	if (info->key.a)
		rotate(info, 1);
	return (0);
}

int		key_press(int key, t_info *info)
{
	if (key == KEY_W || key == KEY_UP)
		info->key.w = 1;
	else if (key == KEY_S || key == KEY_DOWN)
		info->key.s = 1;
	if (key == KEY_A || key == KEY_LEFT)
		info->key.a = 1;
	else if (key == KEY_D || key == KEY_RIGHT)
		info->key.d = 1;
	if (key == KEY_ESC)
		main_close(info);
	return (0);
}

int		key_release(int key, t_info *info)
{
	if (key == KEY_W || key == KEY_UP)
		info->key.w = 0;
	else if (key == KEY_S || key == KEY_DOWN)
		info->key.s = 0;
	else if (key == KEY_A || key == KEY_LEFT)
		info->key.a = 0;
	else if (key == KEY_D || key == KEY_RIGHT)
		info->key.d = 0;
	return (0);
}
