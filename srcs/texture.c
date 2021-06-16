#include "../includes/cub3d.h"

int		tex_init(t_info *info)
{
	int i;
	int j;

	info->texture = (int **)malloc(sizeof(int *) * TEXTURES);
	if (!(info->texture))
		return (-1);
	i = 0;
	while (i < TEXTURES)
	{
		info->texture[i] = (int *)malloc(sizeof(int) *
				(TEX_HEIGHT * TEX_WIDTH));
		if (!(info->texture[i]))
		{
			tex_free(info, i);
			return (-1);
		}
		j = 0;
		while (j < TEX_HEIGHT * TEX_WIDTH)
		{
			info->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img_ptr = mlx_xpm_file_to_image(info->mlx, path,
			&img->width, &img->height);
	if (!(img->img_ptr))
		error_exit(info, "Error: texture loading failed\n", 1);
	img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_l, &img->endian);
	if (!(img->data))
		error_exit(info, "Error: texture data loading failed\n", 1);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			texture[img->width * y + x] = img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img_ptr);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[T_NO], info->conf.tex_path[T_NO], &img);
	load_image(info, info->texture[T_SO], info->conf.tex_path[T_SO], &img);
	load_image(info, info->texture[T_WE], info->conf.tex_path[T_WE], &img);
	load_image(info, info->texture[T_EA], info->conf.tex_path[T_EA], &img);
	if (info->conf.tex_path[T_S])
		load_image(info, info->texture[T_S], info->conf.tex_path[T_S], &img);
}

void	tex_free(t_info *info, int i)
{
	while (i >= 0)
	{
		free(info->texture[i]);
		i--;
	}
	free(info->texture);
}
