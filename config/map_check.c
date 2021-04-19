#include "config.h"

int		check_map_row(t_list *map_buffer)
{
	int row;

	row = 0;
	while (map_buffer)
	{
		map_buffer = map_buffer->next;
		row++;
	}
	return (row);
}

int		check_map_col(t_list *map_buffer)
{
	int col;
	int max_col;

	max_col = 0;
	while (map_buffer)
	{
		col = ft_strlen(map_buffer->content) - 1;
		while (map_buffer->content[col] == ' ')
			col--;
		if (max_col < col + 1)
			max_col = col + 1;
		map_buffer = map_buffer->next;
	}
	return (max_col);
}
