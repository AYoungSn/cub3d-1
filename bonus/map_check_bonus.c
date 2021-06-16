#include "config_bonus.h"

static int		map_init(int dir[2][4])
{
	int r;

	r = -1;
	dir[0][0] = 0;
	dir[0][1] = 0;
	dir[0][2] = 1;
	dir[0][3] = -1;
	while (++r < 4)
		dir[1][3 - r] = dir[0][r];
	return (1);
}

int				check_map(t_config *config, int r, int c, int dir[2][4])
{
	int i;

	i = -1;
	if (r < 0 || c < 0 || r >= config->map_row || c >= config->map_col)
		return (0);
	if (config->map_c[r][c] == 0 || config->map_c[r][c] == ' ')
		return (0);
	if (config->map_c[r][c] == '1' || config->map_c[r][c] == 'x')
		return (1);
	config->map_c[r][c] = 'x';
	while (++i < 4)
		if (!check_map(config, r + dir[0][i], c + dir[1][i], dir))
			return (0);
	return (1);
}

static int		valid_char_map(t_config *config)
{
	int r;
	int c;

	r = -1;
	while (++r < config->map_row)
	{
		c = -1;
		while (++c < config->map_col)
			if (!ft_strrchr(" 01234", config->map_c[r][c]))
				return (0);
	}
	return (1);
}

int				valid_map_check(t_config *config)
{
	int		r;
	int		c;
	int		is_valid;
	int		dir[2][4];

	is_valid = 0;
	if (!valid_char_map(config) || config->map_row <= 2 || config->map_col <= 2
	|| !map_init(dir) || !rotate_map(config))
		return (0);
	r = -1;
	while (++r < config->map_row)
	{
		c = -1;
		while (++c < config->map_col)
			if (ft_strrchr("0234", config->map_c[r][c]))
			{
				is_valid = 1;
				if (check_map(config, r, c, dir) == 0)
					return (0);
			}
	}
	return (is_valid && player_valid_check(config));
}
