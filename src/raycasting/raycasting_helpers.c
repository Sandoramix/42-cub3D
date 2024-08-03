#include "cub3D.h"

void loop_until_hit_wall(t_var *game)
{
	game->dda.hit = 0;
	game->dda.side = 0;
	while (game->dda.hit == 0)
	{
		increase_raylen(game);
		if (game->mapinfo.mtxint[game->dda.map_x][game->dda.map_y] > 0)
			game->dda.hit = 1;
	}
}

void calc_relative_line_height(t_var *game)
{
	game->dda.line_h_px = (int)(game->dda.screen_size_w_px / game->dda.wall_dist);
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
}

void put_line_h_in_perspective(t_var *game)
{
	game->dda.draw_start_px = (-game->dda.line_h_px / 2.0) + ((game->mapinfo.rows_mtx * TILE_SIZE) / 2.0);
	if (game->dda.draw_start_px < 0)
		game->dda.draw_start_px = 0;
	game->dda.draw_end_px = (game->dda.line_h_px / 2) + ((game->mapinfo.rows_mtx * TILE_SIZE) / 2);
	if (game->dda.draw_end_px >= game->dda.screen_size_h_px)
		game->dda.draw_end_px = game->dda.screen_size_h_px - 1;
}