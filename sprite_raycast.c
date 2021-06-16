#include "mlx/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17

# define KEY_ESC 53
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

# define screenWidth 640
# define screenHeight 480
# define mapWidth 24
# define mapHeight 24
# define texWidth 64
# define texHeight 64
# define numSprites 19

typedef struct	s_img
{
	void		*img;
	int			*data;

	int			img_width;
    int         img_height;
    int         size_l;
    int         bpp;
    int         endian;
}               t_img;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct  s_game
{
    void        *mlx;
    void        *win;
    t_img       img;
    int         buf[screenHeight][screenWidth];
	double		zBuffer[screenWidth];
    int         **texture;

    double      posX;
    double      posY;
    double      dirX;
    double      dirY;
    double      planeX;
    double      planeY;

	double		moveSpeed;
	double		rotSpeed;

	int			key_a;
	int			key_w;
	int			key_s;
	int			key_d;
	int			key_esc;
}				t_game;

typedef struct	s_pair
{
	double		first;
	int			second;
}				t_pair;


t_sprite sprite[numSprites] =
{
	{20.5, 11.5, 10}, //green light in front of playerstart
	//green lights in every room
	{18.5,4.5, 10},
	{10.0,4.5, 10},
	{10.0,12.5,10},
	{3.5, 6.5, 10},
	{3.5, 20.5,10},
	{3.5, 14.5,10},
	{14.5,20.5,10},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, 9},
	{18.5, 11.5, 9},
	{18.5, 12.5, 9},

	//some barrels around the map
	{21.5, 1.5, 8},
	{15.5, 1.5, 8},
	{16.0, 1.8, 8},
	{16.2, 1.2, 8},
	{3.5,  2.5, 8},
	{9.5, 15.5, 8},
	{10.0, 15.1,8},
};

int		spriteOrder[numSprites];
double	spriteDistance[numSprites];

int	worldMap[mapWidth][mapHeight] =
	{
	{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
	{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
	{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
	{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
	{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
	{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
	{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
	{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
	{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
	{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
	{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};

void	load_image(t_game *game, int *texture, char *path, t_img *img)
{
    img->img = mlx_xpm_file_to_image(game->mlx, path, &img->img_width, &img->img_height);
    img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
    for (int y = 0;y < img->img_height; y++)
        for (int x = 0;x < img->img_width; x++)
            texture[img->img_width * y + x] = img->data[img->img_width * y + x];
    mlx_destroy_image(game->mlx, img->img);
}

int			key_update(t_game *game);

void		sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0;i < amount;i++)
	{
		for (int j = 0;j < amount - 1;j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void		sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;

	sprites = (t_pair *)malloc(sizeof(t_pair) * amount);
	for (int i = 0;i < amount;i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	for (int i = 0;i < amount;i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

void	draw(t_game *game)
{
	for (int y = 0; y < screenHeight; y++)
	{
		for (int x = 0; x < screenWidth; x++)
		{
			game->img.data[y * screenWidth + x] = game->buf[y][x];
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	calc(t_game *game)
{
	// Wall casting
	for (int x = 0;x < screenWidth;x++)
	{
		double cameraX = 2 * x / (double)screenWidth - 1;
		double rayDirX = game->dirX + game->planeX * cameraX;
		double rayDirY = game->dirY + game->planeY * cameraX;

		int mapX = (int)game->posX;
		int mapY = (int)game->posY;

		double sideDistX, sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX, stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - game->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - game->posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(screenHeight / perpWallDist);

		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		int texNum = worldMap[mapX][mapY] - 1;

		double wallX;
		if (side == 0)
			wallX = game->posY + perpWallDist * rayDirY;
		else
			wallX = game->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;

		// starting texture coordinate
		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;

		for (int y = drawStart; y < drawEnd;y++)
		{
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;

			int color = game->texture[texNum][texWidth * texY + texX];
			
			if (side == 1)
				color = (color >> 1) & 8355711;
		
			game->buf[y][x] = color;
		}

		// floor casting
		double floorXWall, floorYWall;

		if (side == 0 && rayDirX > 0)
		{
			floorXWall = mapX;
			floorYWall = mapY + wallX;
		}
		else if (side == 0 && rayDirX < 0)
		{
			floorXWall = mapX + 1.0;
			floorYWall = mapY + wallX;
		}
		else if (side == 1 && rayDirY > 0)
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY;
		}
		else
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = perpWallDist;
		distPlayer = 0.0;

		if (drawEnd < 0) drawEnd = screenHeight;

		for (int y = drawEnd + 1; y < screenHeight; y++)
		{
			currentDist = screenHeight / (2.0 * y - screenHeight);

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);
			double currentFloorX = weight * floorXWall + (1.0 - weight) * game->posX;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * game->posY;

			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * texWidth) % texWidth;
			floorTexY = (int)(currentFloorY * texHeight) % texHeight;

			int checkerBoardPattern = ((int)(currentFloorX) + (int)(currentFloorY)) % 2;
			int floorTexture;
			if (checkerBoardPattern == 0) floorTexture = 3;
			else floorTexture = 4;

			game->buf[y][x] = (game->texture[floorTexture][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
			game->buf[screenHeight - y][x] = game->texture[6][texWidth * floorTexY + floorTexX];
		}
		// set the zbuffer for the sprite casting
		// 벽과의 수직선 거리만을 포함
		game->zBuffer[x] = perpWallDist;
	}
	// sprite casting
	// sort sprites from far to close
	for (int i = 0;i < numSprites;i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((game->posX - sprite[i].x) * (game->posX - sprite[i].x) + (game->posY - sprite[i].y) * (game->posY - sprite[i].y));
	}
	sortSprites(spriteOrder, spriteDistance, numSprites);
	for (int i = 0;i < numSprites;i++)
	{
		// translate sprite position to relative to camera
		double spriteX = sprite[spriteOrder[i]].x - game->posX;
		double spriteY = sprite[spriteOrder[i]].y - game->posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (game->planeX * game->dirY - game->dirX * game->planeY);

		double transformX = invDet * (game->dirY * spriteX - game->dirX * spriteY);
		double transformY = invDet * (-game->planeY * spriteX + game->planeX * spriteY);

		int spriteScreenX = (int)((screenWidth / 2) * (1 + transformX / transformY));

		// sprite 크기 조절 변수 가로 / 세로
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		// 스크린 위의 물체의 높이 계산
		int spriteHeight = (int)fabs((screenHeight / transformY) / vDiv); // 실제 거리 대신에 transformY 를 사용해서 어안렌즈 효과 방지
		// 현재 줄의 아래 위 위치 계산
		int drawStartY = -spriteHeight / 2 + screenHeight / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + screenHeight / 2 + vMoveScreen;
		if (drawEndY >= screenHeight)
			drawEndY = screenHeight - 1;

		// calculate width of the sprite
		int spriteWidth = (int)fabs((screenHeight / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= screenWidth)
			drawEndX = screenWidth - 1;

		// loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX;stripe < drawEndX;stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256);
			if (transformY > 0 && stripe > 0 && stripe < screenWidth && transformY < game->zBuffer[stripe])
			{
				for (int y = drawStartY; y < drawEndY;y++)
				{
					int d = (y - vMoveScreen) * 256 - screenHeight * 128 + spriteHeight * 128;
					int texY = ((d * texHeight) / spriteHeight) / 256;
					int color = game->texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX];
					if ((color & 0x00FFFFFF) != 0) game->buf[y][stripe] = color;
				}
			}
		}
	}
}

int		main_loop(t_game *game)
{
	calc(game);
	draw(game);
	key_update(game);
	return (0);
}

int     key_update(t_game *game)
{
    if (game->key_esc)
        exit(0);
    if (game->key_w)
    {
		if (!worldMap[(int)(game->posX + game->dirX * game->moveSpeed)][(int)(game->posY + game->dirY * game->moveSpeed)])
		{
			game->posX += game->dirX * game->moveSpeed;
			game->posY += game->dirY * game->moveSpeed;
		}
    }
	if (game->key_s)
    {
        if (!worldMap[(int)(game->posX - game->dirX * game->moveSpeed)][(int)(game->posY - game->dirY * game->moveSpeed)])
		{
			game->posX -= game->dirX * game->moveSpeed;
			game->posY -= game->dirY * game->moveSpeed;
		}
    }
	if (game->key_d)
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(-game->rotSpeed) - game->dirY * sin(-game->rotSpeed);
        game->dirY = oldDirX * sin(-game->rotSpeed) + game->dirY * cos(-game->rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(-game->rotSpeed) - game->planeY * sin(-game->rotSpeed);
        game->planeY = oldPlaneX * sin(-game->rotSpeed) + game->planeY * cos(-game->rotSpeed);
    }
	if (game->key_a)
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(game->rotSpeed) - game->dirY * sin(game->rotSpeed);
        game->dirY = oldDirX * sin(game->rotSpeed) + game->dirY * cos(game->rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(game->rotSpeed) - game->planeY * sin(game->rotSpeed);
        game->planeY = oldPlaneX * sin(game->rotSpeed) + game->planeY * cos(game->rotSpeed);
    }
    return (0);
}

int		key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W || key == 126)
		game->key_w = 1;
	else if (key == KEY_A || key == 123)
		game->key_a = 1;
	else if (key == KEY_S || key == 125)
		game->key_s = 1;
	else if (key == KEY_D || key == 124)
		game->key_d = 1;
	return (0);
}

int		key_release(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W || key == 126)
		game->key_w = 0;
	else if (key == KEY_A || key == 123)
		game->key_a = 0;
	else if (key == KEY_S || key == 125)
		game->key_s = 0;
	else if (key == KEY_D || key == 124)
		game->key_d = 0;
	return (0);
}

void	load_texture(t_game *game)
{
	t_img img;

	load_image(game, game->texture[0], "textures/eagle.xpm", &img);
	load_image(game, game->texture[1], "textures/redbrick.xpm", &img);
	load_image(game, game->texture[2], "textures/purplestone.xpm", &img);
    load_image(game, game->texture[3], "textures/greystone.xpm", &img);
    load_image(game, game->texture[4], "textures/bluestone.xpm", &img);
    load_image(game, game->texture[5], "textures/mossy.xpm", &img);
    load_image(game, game->texture[6], "textures/wood.xpm", &img);
    load_image(game, game->texture[7], "textures/colorstone.xpm", &img);
    load_image(game, game->texture[8], "textures/barrel.xpm", &img);
    load_image(game, game->texture[9], "textures/pillar.xpm", &img);
    load_image(game, game->texture[10], "textures/greenlight.xpm", &img);
}

int		main()
{
	t_game game;
	game.mlx = mlx_init();

	game.posX = 22.0;
	game.posY = 11.5;
	game.dirX = -1.0;
	game.dirY = 0.0;
	game.planeX = 0.0;
	game.planeY = 0.66;
	// dirX 랑 planeY 한쪽이 양수면 반대쪽은 음수
	game.key_a = 0;
	game.key_w = 0;
	game.key_s = 0;
	game.key_d = 0;
	game.key_esc = 0;

	for (int i = 0;i<screenHeight;i++)
	{
		for (int j = 0;j < screenWidth;j++)
			game.buf[i][j] = 0;
	}

	if (!(game.texture = (int**)malloc(sizeof(int*) * 8)))
		return -1;
	for (int i = 0;i < 11;i++)
		if (!(game.texture[i] = (int*)malloc(sizeof(int) * (texHeight * texWidth))))
			return -1;
	for (int i = 0;i < 11;i++)
	{
		for (int j = 0;j < texHeight * texWidth;j++)
			game.texture[i][j] = 0;
	}
	load_texture(&game);

	game.moveSpeed = 0.05;
	game.rotSpeed = 0.05;

	game.win = mlx_new_window(game.mlx, screenWidth, screenHeight, "mlx");

	game.img.img = mlx_new_image(game.mlx, screenWidth, screenHeight);
	game.img.data = (int*)mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.size_l, &game.img.endian);

	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, 0, &key_release, &game);
	mlx_loop(game.mlx);
}