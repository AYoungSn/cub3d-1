#include "config.h"
#include <stdio.h>

int		parse_resolution(t_config *config, char *line)
{
	int		i;

	i = 1;
	if (line && line[0] == 'R')
	{
		while (line[i] && is_space(line[i]))
			i++;
		config->req_width = ft_atoi(line + i);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		config->req_height = ft_atoi(line + i);
		return (1);
	}
	return (-1);
}

int		parse_texture(t_config *config, int id, char *line)
{
	int		i;
	int		len;
	char	*path;

	i = 2;
	while (line[i] == ' ')
		i++;
	line += i;
	if (config->tex_path[id])
	{
		free(config->tex_path[id]);
		config->tex_path[id] = 0;
	}
	len = ft_strlen(line) - 1;
	while (line[len] == ' ')
		len--;
	if (!(path = ft_substr(line, 0, len + 1)))
		return (-1);
	config->tex_path[id] = path;
	return (1);
}

int		str_to_color(char *line)
{
	int rgb;
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	rgb = 0;
	while (line[i] && cnt <= 16)
	{
		while (!ft_strrchr(", ", line[i]))
			i++;
		line[i] = 0;
		rgb = rgb | (ft_atoi(line) << (16 - cnt));
		line += i + 1;
		i = 0;
		cnt += 8;
	}
	return (rgb);
}

int		parse_color(t_config *config, int id, char *line)
{
	int				i;
	unsigned int	color;

	i = 1;
	while (is_space(line[i]))
		i++;
	if (!ft_isdigit(line[i]))
	{
		parse_texture(config, id, line);
		return (0);
	}
	if ((color = (str_to_color(line + i))) < 0)
		return (-1);
	config->cf_color[id - T_SKY] = color;
	return (0);
}
