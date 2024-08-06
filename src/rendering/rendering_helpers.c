#include "cub3D.h"

void increase_raylen(t_var *game)
{
	if (game->dda.ray.x < game->dda.ray.y)
	{	
		game->dda.ray.x += game->dda.delta_dist.x;
		game->dda.map.x += game->dda.step_x;
		game->dda.side = 0;
	}
	else
	{
		game->dda.ray.y += game->dda.delta_dist.y;
		game->dda.map.y += game->dda.step_y;
		game->dda.side = 1;
	}
}

void loop_until_hit_wall(t_var *game)
{
	game->dda.hit = 0;
	game->dda.side = 0;
	while (game->dda.hit == 0)
	{
		increase_raylen(game);
		if(parse_map_chr_at(game,game->dda.map.y,  game->dda.map.x) == 0 ||
			parse_map_chr_at(game, game->dda.map.y,  game->dda.map.x) == MAP_WALL)		
				game->dda.hit = 1;
	}
}


void get_wall_coords(t_var *game)
{
	const int  wall_height = (int)(WINDOW_WIDTH / game->dda.wall_dist);

	if (game->dda.side == 0)
		game->dda.wall_dist = (game->dda.ray.x - game->dda.delta_dist.x);
	else
		game->dda.wall_dist = (game->dda.ray.y - game->dda.delta_dist.y);

	game->dda.wall_start_px = -wall_height / 2.0 + WINDOW_HEIGHT / 2.0 \
		+ game->player.offset + ((game->player.pos_z + game->player.head_pos_z) / game->dda.wall_dist);
	game->dda.wall_end_px = wall_height / 2 + WINDOW_HEIGHT / 2 \
		+ game->player.offset + ((game->player.pos_z + game->player.head_pos_z) / game->dda.wall_dist);
	
	if (game->dda.wall_start_px < 0)
		game->dda.wall_start_px = 0;
	if (game->dda.wall_end_px >= WINDOW_HEIGHT)
		game->dda.wall_end_px = WINDOW_HEIGHT - 1;
}