#ifndef CONFIG_H
# define CONFIG_H

# include "../gnl/get_next_line.h"
# include "../utils/utils.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# define C_R    9
# define C_NO   0
# define C_SO   1
# define C_WE   2
# define C_EA   3
# define C_C    4
# define C_F    5
# define C_S    6
# define C_MAP  7

# define TEXTURES 9
# define T_NO 0
# define T_SO 1
# define T_WE 2
# define T_EA 3
# define T_SKY 4
# define T_FLOOR 5
# define T_SPRITE 6
# define T_SPRITE_UP 7
# define T_SPRITE_C 8

typedef struct	s_config
{
	int			req_height;
	int			req_width;
	char		*tex_path[TEXTURES];
	int			cf_color[2];
	char		**map;
	int			map_row;
	int			map_col;
	int			pos_x;
	int			pos_y;
}				t_config;

int				identifier(char *line);
int				parse_line(t_config *config, char *line, t_list **map_buffer);
int				parse_config(t_config *config, char *conf_path);
void			config_init(t_config *config);
void			clear_config(t_config *config);

int				parse_resolution(t_config *config, char *line);
int				parse_texture(t_config *config, int id, char *line);
int				str_to_color(char *line);
int				parse_color(t_config *config, int id, char *line);

void			player_set(t_config *config, int x, int y);
int				parse_map(t_config *config, t_list *map_buffer);
void			copy_map(t_config *config, t_list *map_buffer);
int				check_map_row(t_list *map_buffer);
int				check_map_col(t_list *map_buffer);
#endif
