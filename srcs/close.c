#include "../includes/cub3d.h"

int		error_exit(t_info *info, char *message, int status)
{
	write(2, message, ft_strlen(message));
	clear_game(info, status);
	exit(-1);
	return (-1);
}

void	buf_free(t_info *info, int i)
{
	while (i >= 0)
	{
		free(info->buf[i]);
		i--;
	}
	free(info->buf);
}

void	clear_game(t_info *info, int status)
{
	if (info)
	{
		if (status != 0)
			clear_config(&info->conf, status);
		if (info->buf)
			buf_free(info, info->conf.win_height - 1);
		if (info->texture)
			tex_free(info, TEXTURES - 1);
		if (info->zBuffer)
			free(info->zBuffer);
		if (info->sprite)
			free(info->sprite);
		clear_window(info);
	}
}

