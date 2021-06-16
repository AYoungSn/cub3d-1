#include "../includes/cub3d_bonus.h"

int		key_update(t_info *info)
{
	if (info->key.w)
		move_vertical(info, 1);
	if (info->key.s)
		move_vertical(info, -1);
	if (info->key.a)
		move_horizontal(info, -1);
	if (info->key.d)
		move_horizontal(info, 1);
	if (info->key.right)
		rotate(info, 1);
	if (info->key.left)
		rotate(info, -1);
	return (0);
}

int		key_press(int key, t_info *info)
{
	if (key == KEY_W)
		info->key.w = 1;
	else if (key == KEY_S)
		info->key.s = 1;
	if (key == KEY_A)
		info->key.a = 1;
	else if (key == KEY_D)
		info->key.d = 1;
	if (key == KEY_LEFT)
		info->key.left = 1;
	if (key == KEY_RIGHT)
		info->key.right = 1;
	if (key == KEY_ESC)
		main_close(info);
	return (0);
}

int		key_release(int key, t_info *info)
{
	if (key == KEY_W)
		info->key.w = 0;
	else if (key == KEY_S)
		info->key.s = 0;
	else if (key == KEY_A)
		info->key.a = 0;
	else if (key == KEY_D)
		info->key.d = 0;
	else if (key == KEY_LEFT)
		info->key.left = 0;
	else if (key == KEY_RIGHT)
		info->key.right = 0;
	return (0);
}
