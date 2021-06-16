#include "config.h"

int			parse_resolution(t_config *config, char *line)
{
	int		i;

	i = 1;
	config->set[C_R] = 1;
	if (line && line[0] == 'R')
	{
		i = notspace_index(line, i);
		if (ft_strlen(line + i) == 0)
			return (0);
		if (ft_isdigit(line[i]))
			config->win_width = ft_atoi(line + i);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		i = notspace_index(line, i);
		if (ft_isdigit(line[i]))
			config->win_height = ft_atoi(line + i);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		i = notspace_index(line, i);
		if (line[i] != 0 || config->win_height < 0 || config->win_width < 0)
			return (0);
		return (1);
	}
	return (0);
}

int			parse_texture(t_config *config, int id, char *line)
{
	int		i;
	int		len;
	char	*path;

	i = 2;
	config->set[id] = 1;
	line += notspace_index(line, i);
	if (ft_strlen(line) == 0)
		return (0);
	if (config->tex_path[id])
	{
		free(config->tex_path[id]);
		config->tex_path[id] = 0;
	}
	len = ft_strlen(line) - 1;
	while (line[len] == ' ')
		len--;
	i = 0;
	while (i < len + 1)
		if (is_space(line[i++]))
			return (0);
	if (!(path = ft_substr(line, 0, len + 1)))
		return (0);
	config->tex_path[id] = path;
	return (1);
}

static int	color_split(char *line)
{
	int i;
	int cnt;
	int	len;

	len = ft_strlen(line);
	cnt = 0;
	while (is_space(line[--len]))
		line[len] = 0;
	i = 0;
	while (i < len + 1)
	{
		if (line[i] == ',')
			cnt++;
		if (line[i] != ',' && !ft_isdigit(line[i]))
			return (0);
		i++;
	}
	if (cnt == 2)
		return (1);
	return (0);
}

int			str_to_color(char *line)
{
	int rgb;
	int i;
	int cnt;
	int num;

	i = 0;
	cnt = 0;
	rgb = 0;
	if (!color_split(line))
		return (-1);
	while (line[i] != ',' && line[i] && cnt <= 16)
	{
		num = ft_atoi(line + i);
		if (num > 255 || num < 0)
			return (-1);
		rgb = (rgb | (num << (16 - cnt)));
		cnt += 8;
		i = notspace_index(line, i);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		if (line[i] == ',')
			i++;
	}
	return (rgb);
}

int			parse_color(t_config *config, int id, char *line)
{
	int				i;
	unsigned int	color;

	i = notspace_index(line, 1);
	if (ft_strlen(line + i) == 0)
		return (0);
	if (!ft_isdigit(line[i]))
		return (0);
	if ((int)(color = str_to_color(line + i)) < 0)
		return (0);
	config->cf_color[id - T_C] = color;
	config->set[id] = 1;
	return (1);
}
