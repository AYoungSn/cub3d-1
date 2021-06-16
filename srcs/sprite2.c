#include "../includes/cub3d.h"

void	calc_sprite_pos(t_sprt_line *sprt, int *order, t_info *info, int i)
{
	double	inv_det;

	sprt->x = info->sprite[order[i]].x - info->posX;
	sprt->y = info->sprite[order[i]].y - info->posY;
	inv_det = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY);
	sprt->transX = inv_det * (info->dirY * sprt->x - info->dirX * sprt->y);
	sprt->transY = inv_det * (-info->planeY * sprt->x + info->planeX * sprt->y);
	sprt->screenX = (int)((info->conf.win_width / 2)
				* (1 + sprt->transX / sprt->transY));
}

void	calc_sprite_line(t_sprt_line *sprt, t_info *info)
{
	sprt->vMoveScreen = (int)(V_MOVE / sprt->transY);
	sprt->height = (int)fabs((info->conf.win_height / sprt->transY) / V_DIV);
	sprt->drawStartY = -sprt->height / 2 + info->conf.win_height
						/ 2 + sprt->vMoveScreen;
	if (sprt->drawStartY < 0)
		sprt->drawStartY = 0;
	sprt->drawEndY = sprt->height / 2 + info->conf.win_height
						/ 2 + sprt->vMoveScreen;
	if (sprt->drawEndY >= info->conf.win_height)
		sprt->drawEndY = info->conf.win_height - 1;
	sprt->width = (int)fabs((info->conf.win_height / sprt->transY) / U_DIV);
	sprt->drawStartX = -sprt->width / 2 + sprt->screenX;
	if (sprt->drawStartX < 0)
		sprt->drawStartX = 0;
	sprt->drawEndX = sprt->width / 2 + sprt->screenX;
	if (sprt->drawEndX >= info->conf.win_width)
		sprt->drawEndX = info->conf.win_width - 1;
}

void	coord_sprite_tex(t_info *info, int *order, t_sprt_line *sprt, int i)
{
	int	stripe;
	int	y;
	int	d;

	stripe = sprt->drawStartX - 1;
	while (++stripe < sprt->drawEndX)
	{
		sprt->texX = (int)((256 * (stripe - (-sprt->width / 2 + sprt->screenX))
					* TEX_WIDTH / sprt->width) / 256);
		if (sprt->transY > 0 && stripe > 0 && stripe < info->conf.win_width
					&& sprt->transY < info->zBuffer[stripe])
		{
			y = sprt->drawStartY - 1;
			while (++y < sprt->drawEndY)
			{
				d = (y - sprt->vMoveScreen) * 256 - info->conf.win_height * 128
					+ sprt->height * 128;
				sprt->texY = ((d * TEX_HEIGHT) / sprt->height) / 256;
				sprt->color = info->texture[info->sprite[order[i]].texture]
							[TEX_WIDTH * sprt->texY + sprt->texX];
				if ((sprt->color & 0x00FFFFFF) != 0)
					info->buf[y][stripe] = sprt->color;
			}
		}
	}
}
