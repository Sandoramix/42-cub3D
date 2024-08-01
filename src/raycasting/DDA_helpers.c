#include "cub3D.h"


void calc_initial_step_intial_raylen(t_var *game)
{

	if (game->dda_helper.rayDirX < 0)
	{
		game->dda_helper.stepX = -1;
		game->dda_helper.sideDistX = (game->playerPos.pos_x - game->dda_helper.mapX) * game->dda_helper.deltaDistX;
	}
	else
	{
		game->dda_helper.stepX = 1;
		game->dda_helper.sideDistX = (game->dda_helper.mapX + 1.0 - game->playerPos.pos_x) * game->dda_helper.deltaDistX;
	}
	if (game->dda_helper.rayDirY < 0)
	{
		game->dda_helper.stepY = -1;
		game->dda_helper.sideDistY = (game->playerPos.pos_y - game->dda_helper.mapY) * game->dda_helper.deltaDistY;
	}
	else
	{
		game->dda_helper.stepY = 1;
		game->dda_helper.sideDistY = (game->dda_helper.mapY + 1.0 - game->playerPos.pos_y) * game->dda_helper.deltaDistY;
	}
}

void increase_raylen(t_var *game)
{
	if (game->dda_helper.sideDistX < game->dda_helper.sideDistY)
	{
		game->dda_helper.sideDistX += game->dda_helper.deltaDistX;
		game->dda_helper.mapX += game->dda_helper.stepX;
		game->dda_helper.side = 0;
	}
	else
	{
		game->dda_helper.sideDistY += game->dda_helper.deltaDistY;
		game->dda_helper.mapY += game->dda_helper.stepY;
		game->dda_helper.side = 1;
	}
}

void calc_distance_from_wall(t_var *game)
{
	if (game->dda_helper.side == 0)
		game->dda_helper.perpWallDist = (game->dda_helper.sideDistX - game->dda_helper.deltaDistX);
	else
		game->dda_helper.perpWallDist = (game->dda_helper.sideDistY - game->dda_helper.deltaDistY);

	//printf("perpWallDistance = %f\n", game->dda_helper.perpWallDist);
	
}

void calc_perspective(t_var *game)
{
	game->dda_helper.draw_start = (-game->dda_helper.lineHeight / 2.0) + ((game->mapinfo.rows_mtx * TILE_SIZE) / 2.0);
	if (game->dda_helper.draw_start < 0)
		game->dda_helper.draw_start = 0;
	game->dda_helper.draw_end = (game->dda_helper.lineHeight / 2) + ((game->mapinfo.rows_mtx * TILE_SIZE) / 2);
	if (game->dda_helper.draw_end >= game->mapinfo.rows_mtx * TILE_SIZE)
		game->dda_helper.draw_end = game->mapinfo.rows_mtx * TILE_SIZE - 1;
}