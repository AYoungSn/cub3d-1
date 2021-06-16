#include "bonus/config_bonus.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	t_config config;

	if (argc < 2 || (argc == 3 && !ft_strcmp(argv[2], "--save")))
		return (write(2, "Error\n", 6));
	if (!parse_config(&config, argv[1]))
	{
		clear_config(&config, -1);
		return (write(2, "Error\n", 6));
	}
	printf("height: %d, width: %d\n", config.win_height, config.win_width);
	printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", config.tex_path[T_NO], config.tex_path[T_SO], config.tex_path[T_WE], config.tex_path[T_EA]);
	if (config.tex_path[T_F])
		printf("FLOOR: %s\n", config.tex_path[T_F]);
	else
		printf("FLOOR: %X\n", config.cf_color[1]);
	if (config.tex_path[T_C])
		printf("SKY: %s\n", config.tex_path[T_C]);
	else
		printf("SKY: %X\n", config.cf_color[0]);
	printf("SPRITE: %s\n", config.tex_path[T_S]);
	if (config.tex_path[T_SC])
		printf("SPRITE C: %s\n", config.tex_path[T_SC]);
	if (config.tex_path[T_SU])
		printf("SPRITE UP: %s\n", config.tex_path[T_SU]);
	printf("MAP\n");
	int i, j;
	i = 0;
	printf("map row: %d, col: %d\n", config.map_row, config.map_col);
	printf("pos_x: %d, pos_y: %d\n", config.pos_x, config.pos_y);
	while (i < config.map_row)
	{
		j = 0;
		while (j < config.map_col)
			printf("%c", config.map[i][j++]);
		printf("\n");
		i++;
	}
	clear_config(&config, 1);
	return (0);
}
