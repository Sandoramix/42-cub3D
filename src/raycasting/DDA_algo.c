#include <libft.h>
#include "cub3D.h"

static void DDA_core_logic(t_var *game, int x)
{
	int y;

	calc_initial_step_intial_raylen(game);
	while (!game->dda_helper.hit_wall)
	{
		increase_raylen(game);
		if (game->mtxint[game->dda_helper.mapX][game->dda_helper.mapY] > 0)
			game->dda_helper.hit_wall = 1;
	}
	calc_distance_from_wall(game);
	game->dda_helper.lineHeight = (game->rows_mtx * TEXTURE_SIZE) / game->dda_helper.perpWallDist;
	calc_perspective(game);
	dbg_printf("x: %d, sideDistX: %f, sideDistY: %f, perpWallDist: %f, lineHeight: %d, draw_start: %d, draw_end: %d\n",
			   x, game->dda_helper.sideDistX, game->dda_helper.sideDistY, game->dda_helper.perpWallDist, game->dda_helper.lineHeight, game->dda_helper.draw_start, game->dda_helper.draw_end);
	y = game->dda_helper.draw_start;

	int print_every_tot_line = 6;
	if (x % print_every_tot_line == 0)
	{
		while (y <= game->dda_helper.draw_end)
		{
			mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, 0xFF0000);
			y++;
		}
	}
}

static void get_multiplication_factor(t_var *game)
{
	// lunghezza da percorrere lungo il per spostarsi di 1 sull asse x e y, poi verranno confrontati per decidere dove
	// fare il prossimo passo ("StepX/StepY")
	game->dda_helper.deltaDistX = fabs(1 / game->dda_helper.rayDirX);
	game->dda_helper.deltaDistY = fabs(1 / game->dda_helper.rayDirY);
}

static void get_ray_direction(t_var *game, int pixel_pos_x)
{
	// right side of screen will get coordinate 1,
	// center 0,
	// left 	-1.
	game->dda_helper.cameraX = 2 * pixel_pos_x / game->dda_helper.screenSize - 1;
	// direction of the ray

	game->dda_helper.rayDirX = game->playerPos.dir_x + game->plane.x * game->dda_helper.cameraX;
	game->dda_helper.rayDirY = game->playerPos.dir_y + game->plane.y * game->dda_helper.cameraX;
}

void calculate_DDA(t_var *game)
{
	game->dda_helper = (t_DDA){0};
	int pixel_pos_x;

	pixel_pos_x = 0;
	game->dda_helper.screenSize = game->cols_mtx * TEXTURE_SIZE;
	game->dda_helper.mapX = (int)game->playerPos.pos_x / TEXTURE_SIZE;
	game->dda_helper.mapY = (int)game->playerPos.pos_y / TEXTURE_SIZE;
	while (pixel_pos_x < game->dda_helper.screenSize)
	{
		get_ray_direction(game, pixel_pos_x);
		get_multiplication_factor(game);
		DDA_core_logic(game, pixel_pos_x);
		pixel_pos_x++;
	}
}