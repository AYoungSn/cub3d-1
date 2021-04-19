#include "config.h"

int		identifier(char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (C_R);
	else if (line[0] == 'N' && line[1] == 'O')
		return (C_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (C_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (C_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (C_EA);
	else if (line[0] == 'S' && line[1] == ' ')
		return (C_S);
	else if (line[0] == 'F' && line[1] == ' ')
		return (C_F);
	else if (line[0] == 'C' && line[1] == ' ')
		return (C_C);
	else
		return (C_MAP);
}

int		parse_line(t_config *config, char *line, t_list **map_buffer)
{
	int	id;
	int len;

	if ((len = ft_strlen(line)) == 0)
		return (0);
	id = identifier(line);
	if (id == C_R)
		return (parse_resolution(config, line));
	else if ((id >= C_NO && id <= C_EA) || id == C_S)
		return (parse_texture(config, id, line));
	else if (id == C_F || id == C_C)
		return (parse_color(config, id, line));
	return (!!lst_add_back(map_buffer, ft_strdup(line)));
}

void	config_init(t_config *config)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
		config->tex_path[i++] = 0;
	config->map = NULL;
}

int		parse_config(t_config *config, char *path)
{
	int		fd;
	char	*line;
	t_list	*map_buffer;

	if (!(ft_endcmp(path, ".cub")))
		return (0);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	config_init(config);
	map_buffer = 0;
	while (get_next_line(fd, &line))
	{
		parse_line(config, line, &map_buffer);
		free(line);
	}
	if (ft_strlen(line) > 0)
		lst_add_back(&map_buffer, ft_strdup(line));
	free(line);
	close(fd);
	if (!parse_map(config, map_buffer))
		return (lst_clear(&map_buffer));
	lst_clear(&map_buffer);
	return (1);
}

void	clear_config(t_config *config)
{
	int i;

	i = 0;
	while (i < TEXTURES)
	{
		if (config->tex_path[i])
			free(config->tex_path[i]);
		i++;
	}
}
