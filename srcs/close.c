#include "../includes/cub3d.h"

void	tex_free(t_info *info, int i)
{
	while (i >= 0)
	{
		free(info->texture[i]);
		i--;
	}
	free(info->texture);
}


