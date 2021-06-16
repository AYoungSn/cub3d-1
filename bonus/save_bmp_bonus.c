#include "../includes/cub3d_bonus.h"

static int	write_bmp_data(int fd, t_info *info, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = info->conf.win_height;
	while (--i >= 0)
	{
		j = -1;
		while (++j < info->conf.win_width)
		{
			color = info->buf[i][j];
			if ((write(fd, &color, 3) < 0))
				return (0);
		}
		if (pad > 0 && write(fd, &zero, pad) < 0)
			return (0);
	}
	return (1);
}

static void	set_int_in_char(unsigned char *arr, int val)
{
	arr[0] = (unsigned char)val;
	arr[1] = (unsigned char)(val >> 8);
	arr[2] = (unsigned char)(val >> 16);
	arr[3] = (unsigned char)(val >> 24);
}

int			write_bmp_header(int fd, int filesize, t_info *info)
{
	int				i;
	unsigned char	file_header[54];

	i = -1;
	while (++i < 54)
		file_header[i] = (unsigned char)(0);
	file_header[0] = (unsigned char)'B';
	file_header[1] = (unsigned char)'M';
	set_int_in_char(file_header + 2, filesize);
	file_header[10] = (unsigned char)(54);
	file_header[14] = (unsigned char)(40);
	i = info->conf.win_width;
	set_int_in_char(file_header + 18, i);
	i = info->conf.win_height;
	set_int_in_char(file_header + 22, i);
	file_header[27] = (unsigned char)1;
	file_header[28] = (unsigned char)24;
	if (write(fd, file_header, 54) != 54)
		return (0);
	return (1);
}

int			save_image(t_info *info)
{
	int		file;
	int		filesize;
	int		pad;

	calc_back(info);
	calc_sprite(info);
	calc_minimap(info);
	draw(info);
	if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (0);
	pad = (4 - (info->conf.win_width * 3) % 4) % 4;
	filesize = 54 + (3 * (info->conf.win_width + pad) * info->conf.win_width);
	if (!write_bmp_header(file, filesize, info))
		return (1);
	if (!write_bmp_data(file, info, pad))
		return (1);
	close(file);
	clear_game(info, 1);
	return (0);
}
