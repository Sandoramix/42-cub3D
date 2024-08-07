#include "cub3D.h"

void increase_raylen(t_var *game)
{
		if (game->raycasting.ray.x < game->raycasting.ray.y)
		{	
			game->raycasting.ray.x += game->raycasting.delta_dist.x;
			game->raycasting.map_coords.x += game->raycasting.step_x;
			if (game->raycasting.step_x > 0)
   				game->raycasting.side = CNF_WALL_EAST;
			else
    			game->raycasting.side = CNF_WALL_WEST;
		}
		else
		{
			game->raycasting.ray.y += game->raycasting.delta_dist.y;
			game->raycasting.map_coords.y += game->raycasting.step_y;
			if (game->raycasting.step_y > 0)
				game->raycasting.side = CNF_WALL_NORD;
			else
				game->raycasting.side = CNF_WALL_SOUTH;
		}
}

void loop_until_hit_wall(t_var *game)
{
	game->raycasting.hit = 0;
	game->raycasting.side = 0;
	while (game->raycasting.hit == 0)
	{
		increase_raylen(game);
		if(parse_map_chr_at(game,game->raycasting.map_coords.y,  game->raycasting.map_coords.x) == 0 ||
			parse_map_chr_at(game, game->raycasting.map_coords.y,  game->raycasting.map_coords.x) == MAP_WALL)		
				game->raycasting.hit = 1;
	}
}


void get_wall_coords(t_var *game)
{
	const int  wall_height = (int)(game->config._w / game->raycasting.wall_dist);

	if (game->raycasting.side == CNF_WALL_WEST || game->raycasting.side == CNF_WALL_EAST)
		game->raycasting.wall_dist = (game->raycasting.ray.x - game->raycasting.delta_dist.x);
	else
		game->raycasting.wall_dist = (game->raycasting.ray.y - game->raycasting.delta_dist.y);

	game->raycasting.wall_start_px = -wall_height / 2.0 + game->config._h / 2.0 \
		+ game->player.offset + ((game->player.pos_z + game->player.head_pos_z) / game->raycasting.wall_dist);
	game->raycasting.wall_end_px = wall_height / 2 + game->config._h / 2 \
		+ game->player.offset + ((game->player.pos_z + game->player.head_pos_z) / game->raycasting.wall_dist);
	
	if (game->raycasting.wall_start_px < 0)
		game->raycasting.wall_start_px = 0;
	if (game->raycasting.wall_end_px >= game->config._h)
		game->raycasting.wall_end_px = game->config._h - 1;
}