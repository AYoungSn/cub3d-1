#ifndef CONFIG_BONUS_H
# define CONFIG_BONUS_H

# include "../gnl/get_next_line.h"
# include "../utils/utils.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# define C_R    10
# define C_NO   0
# define C_SO   1
# define C_WE   2
# define C_EA   3
# define C_S    4
# define C_SU	5
# define C_SC	6
# define C_C    7
# define C_F    8
# define C_MAP  9

# define TEXTURES 9
# define T_NO 0
# define T_SO 1
# define T_WE 2
# define T_EA 3
# define T_S 4
# define T_SU 5
# define T_SC 6
# define T_C 7
# define T_F 8

typedef struct	s_config
{
	int			win_width;
	int			win_height;
	char		*tex_path[TEXTURES];
	int			cf_color[2];
	char		**map;
	char		**map_c;
	int			map_row;
	int			map_col;
	int			pos_x;
	int			pos_y;
	char		dir;
	int			set[11];
}				t_config;

int				identifier(char *line);
int				parse_line(t_config *config, char *line, t_list **map_buffer);
int				parse_config(t_config *config, char *conf_path);
void			config_init(t_config *config);
int				clear_config(t_config *config, int status);

int				parse_resolution(t_config *config, char *line);
int				parse_texture(t_config *config, int id, char *line);
int				str_to_color(char *line);
int				parse_color(t_config *config, int id, char *line);

int				player_set(t_config *config, int x, int y);
int				parse_map(t_config *config, t_list *map_buffer);
int				copy_map(t_config *config, t_list *map_buffer);
int				check_map_row(t_list *map_buffer);
int				check_map_col(t_list *map_buffer);
int				check_map(t_config *config, int r, int c, int dir[2][4]);
int				valid_map_check(t_config *config);
int				element_check(int set[]);
int				player_valid_check(t_config *config);
int				rotate_map(t_config *config);
int				notspace_index(char *line, int ind);

#endif
