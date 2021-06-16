#include "../includes/cub3d_bonus.h"

int		element_check(int set[])
{
	int i;

	i = -1;
	while (++i < 11)
		if (set[i] == 0 && i != C_S
		&& i != C_SC && i != C_SU)
			return (0);
	return (1);
}

int		rotate_map(t_config *config)
{
	int		i;
	int		j;

	i = -1;
	if (!(config->map = malloc(sizeof(char*) * config->map_col)))
		return (0);
	while (++i < config->map_col)
		if (!(config->map[i] = malloc(sizeof(char) * config->map_row)))
			return (0);
	i = -1;
	while (++i < config->map_row)
	{
		j = -1;
		while (++j < config->map_col)
			config->map[j][i] = config->map_c[i][j];
	}
	return (1);
}

int		player_valid_check(t_config *config)
{
	int		r;
	int		c;

	r = config->pos_y;
	c = config->pos_x;
	if (r <= 0 || r >= config->map_row - 1
	|| c <= 0 || c >= config->map_col - 1)
		return (0);
	if (!ft_strrchr("12x", config->map_c[r][c + 1])
	|| !ft_strrchr("12x", config->map_c[r][c - 1])
	|| !ft_strrchr("12x", config->map_c[r + 1][c])
	|| !ft_strrchr("12x", config->map_c[r - 1][c]))
		return (0);
	return (1);
}

int		notspace_index(char *line, int ind)
{
	while (line[ind] && line[ind] == ' ')
		ind++;
	return (ind);
}
