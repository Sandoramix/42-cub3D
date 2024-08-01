#include "cub3D.h"


void calc_initial_step_intial_raylen(t_var *game)
{

	if (game->dda.dir_rayx < 0)
	{
		game->dda.step_x = -1;
		game->dda.side_dist_x = (game->player_pos.x - game->dda.map_x) * game->dda.delta_dist_x;
	}
	else
	{
		game->dda.step_x = 1;
		game->dda.side_dist_x = (game->dda.map_x + 1.0 - game->player_pos.x) * game->dda.delta_dist_x;
	}
	if (game->dda.dir_rayy < 0)
	{
		game->dda.ste_y = -1;
		game->dda.side_dist_y = (game->player_pos.y - game->dda.map_y) * game->dda.delta_dist_y;
	}
	else
	{
		game->dda.ste_y = 1;
		game->dda.side_dist_y = (game->dda.map_y + 1.0 - game->player_pos.y) * game->dda.delta_dist_y;
	}
}

void increase_raylen(t_var *game)
{
	if (game->dda.side_dist_x < game->dda.side_dist_y)
	{
		game->dda.side_dist_x += game->dda.delta_dist_x;
		game->dda.map_x += game->dda.step_x;
		game->dda.side = 0;
	}
	else
	{
		game->dda.side_dist_y += game->dda.delta_dist_y;
		game->dda.map_y += game->dda.ste_y;
		game->dda.side = 1;
	}
}

void calc_distance_from_wall(t_var *game)
{
	if (game->dda.side == 0)
		game->dda.wall_dist = (game->dda.side_dist_x - game->dda.delta_dist_x);
	else
		game->dda.wall_dist = (game->dda.side_dist_y - game->dda.delta_dist_y);
	//printf("wall_distance = %f\n", game->dda.wall_dist);
}

void put_line_h_in_perspective(t_var *game)
{
	game->dda.draw_start_px = (-game->dda.line_h_px / 2.0) + ((game->mapinfo.rows_mtx * TILE_SIZE) / 2.0);
	if (game->dda.draw_start_px < 0)
		game->dda.draw_start_px = 0;
	game->dda.draw_end_px = (game->dda.line_h_px / 2) + ((game->mapinfo.rows_mtx * TILE_SIZE) / 2);
	if (game->dda.draw_end_px >= game->mapinfo.rows_mtx * TILE_SIZE)
		game->dda.draw_end_px = game->mapinfo.rows_mtx * TILE_SIZE - 1;

	//printf("draw start / end %f %f\n", game->dda.draw_start_px ,game->dda.draw_end_px );
}