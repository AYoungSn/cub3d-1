#include "config.h"

void	player_set(t_config *config, int x, int y)
{
	config->pos_x = x;
	config->pos_y = y;
	config->map[y][x] = '0';
}

void	copy_map(t_config *config, t_list *map_buffer)
{
	int		i;
	int		j;

	i = 0;
	while (i < config->map_row)
	{
		j = 0;
		while (j < config->map_col)
		{
			if (!(map_buffer->content[j]))
			{
				while (j < config->map_col)
					config->map[i][j++] = ' ';
				break ;
			}
			config->map[i][j] = map_buffer->content[j];
			if (ft_strrchr("NSWE", config->map[i][j]))
				player_set(config, j, i);
			j++;
		}
		config->map[i][config->map_col] = 0;
		map_buffer = map_buffer->next;
		i++;
	}
}

int		parse_map(t_config *config, t_list *map_buffer)
{
	int	i;

	if (!(config->map_row = check_map_row(map_buffer)))
		return (0);
	if (!(config->map_col = check_map_col(map_buffer)))
		return (0);
	if (!(config->map = malloc(sizeof(char*) * (config->map_row + 1))))
		return (0);
	i = 0;
	while (i < config->map_row)
		if (!(config->map[i++] = malloc(sizeof(char) * (config->map_col + 1))))
			return (-1);
	copy_map(config, map_buffer);
	config->map[config->map_row] = 0;
	return (1);
}
