#include "cub3D.h"

void increase_raylen(t_var *game)
{
		if (game->engine.ray.x < game->engine.ray.y)
		{	
			game->engine.ray.x += game->engine.delta_dist.x;
			game->engine.map_coords.x += game->engine.step_x;
			if (game->engine.step_x > 0)
   				game->engine.side = CNF_WALL_EAST;
			else
    			game->engine.side = CNF_WALL_WEST;
		}
		else
		{
			game->engine.ray.y += game->engine.delta_dist.y;
			game->engine.map_coords.y += game->engine.step_y;
			if (game->engine.step_y > 0)
				game->engine.side = CNF_WALL_NORD;
			else
				game->engine.side = CNF_WALL_SOUTH;
		}
}

void loop_until_hit_wall(t_var *game)
{
	game->engine.hit = 0;
	game->engine.side = 0;
	while (game->engine.hit == 0)
	{
		increase_raylen(game);
		if(parse_map_chr_at(game,game->engine.map_coords.y,  game->engine.map_coords.x) == 0 ||
			parse_map_chr_at(game, game->engine.map_coords.y,  game->engine.map_coords.x) == MAP_WALL)		
				game->engine.hit = 1;
	}
}


void get_wall_coords(t_var *game)
{
	const int  wall_height = (int)(game->config._w / game->engine.wall_dist);

	if (game->engine.side == CNF_WALL_WEST || game->engine.side == CNF_WALL_EAST)
		game->engine.wall_dist = (game->engine.ray.x - game->engine.delta_dist.x);
	else
		game->engine.wall_dist = (game->engine.ray.y - game->engine.delta_dist.y);

	game->engine.wall_ceil = -wall_height / 2.0 + game->config._h / 2.0 \
		+ game->player.offset + ((game->player.pos_z + game->player.head_pos_z) / game->engine.wall_dist);
	game->engine.wall_floor = wall_height / 2 + game->config._h / 2 \
		+ game->player.offset + ((game->player.pos_z + game->player.head_pos_z) / game->engine.wall_dist);
	
	if (game->engine.wall_ceil < 0)
		game->engine.wall_ceil = 0;
	if (game->engine.wall_floor >= game->config._h)
		game->engine.wall_floor = game->config._h - 1;
}