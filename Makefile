NAME		= cub3d

INC_PATH	= ./includes
SRC_PATH	= ./srcs
MLX_PATH	= ./mlx

INCS		= -I $(INC_PATH)
SRCS		= $(addprefix $(SRC_PATH)/, $(SRC_LIST))
OBJS		= $(SRCS:.c=.o)

SRC_LIST	= main.c init.c close.c key_handling.c wall1.c wall2.c \
			  texture.c floor.c sprite.c

CC			= gcc
CFLAGS		= -O3 -Wall -Wextra -Werror
MLXFLAGS	= -lmlx -framework OpenGL -framework AppKit
MLX			= libmlx.dylib

.c.o:
		$(CC) $(CFLAGS) $(INCS) -c $< -o $(<:.c=.o)

$(NAME):	$(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) -L $(MLX_PATH) $(MLXFLAGS) $(OBJS)
	@install_name_tool -change libmlx.dylib @loader_path/mlx/libmlx.dylib cub3d
	@echo $(NAME) : Created

$(MLX):
	@$(MAKE) -C mlx

all:	$(NAME)

clean:
	@$(MAKE) -C mlx clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(MLX)

re:		fclean all

.PHONY: all clean fclean re
