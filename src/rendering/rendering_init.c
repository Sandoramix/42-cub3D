#include <libft.h>
#include "cub3D.h"

static void calc_initial_step_and_intial_raylen(t_var *game)
{
	if (game->dda.dir_rayx < 0)
	{
		game->dda.step_x = -1;
		game->dda.side_dist_x = (game->player.x_px / 64 - game->dda.map_x) * game->dda.delta_dist_x;
	}
	else
	{
		game->dda.step_x = 1;
		game->dda.side_dist_x = (game->dda.map_x + 1.0 - game->player.x_px / 64) * game->dda.delta_dist_x;
	}
	if (game->dda.dir_rayy < 0)
	{
		game->dda.ste_y = -1;
		game->dda.side_dist_y = (game->player.y_px / 64 - game->dda.map_y) * game->dda.delta_dist_y;
	}
	else
	{
		game->dda.ste_y = 1;
		game->dda.side_dist_y = (game->dda.map_y + 1.0 - game->player.y_px / 64) * game->dda.delta_dist_y;
	}
}

static void calc_multiplication_factor(t_var *game)
{
	game->dda.delta_dist_x = fabs(1 / game->dda.dir_rayx);
	game->dda.delta_dist_y = fabs(1 / game->dda.dir_rayy);
}

static void calc_ray_direction(t_var *game, int pixel_pos_x)
{
	game->dda.camera_x = (double)(2 * pixel_pos_x) / (double)game->dda.screen_size_w_px - 1;
	game->dda.dir_rayx = game->player.dir_y + game->plane.x * game->dda.camera_x;
	game->dda.dir_rayy = game->player.dir_x + game->plane.y * game->dda.camera_x;
}

static void copy_player_pos(t_var *game)
{
	game->dda.map_x = (int)game->player.x_px / 64;
	game->dda.map_y = (int)game->player.y_px / 64;
}

void init_rendering(t_var *game, int pixel_pos_x)
{
	copy_player_pos(game);
	calc_ray_direction(game, pixel_pos_x);
	calc_multiplication_factor(game);
	calc_initial_step_and_intial_raylen(game);
}