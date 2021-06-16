#include "../includes/cub3d.h"

int		window_init(t_info *info)
{
	info->mlx = mlx_init();
	if (!(info->mlx))
		return (-1);
	info->win = mlx_new_window(info->mlx,
				info->conf.win_width, info->conf.win_height, "cub3D");
	if (!(info->win))
		return (-1);
	info->img.img_ptr = mlx_new_image(info->mlx,
						info->conf.win_width, info->conf.win_height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img_ptr, &info->img.bpp,
			&info->img.size_l, &info->img.endian);
	return (0);
}

void	clear_window(t_info *info)
{
	if (info->img.img_ptr)
		mlx_destroy_image(info->mlx, info->img.img_ptr);
	if (info->mlx && info->win)
		mlx_destroy_window(info->mlx, info->win);
}
