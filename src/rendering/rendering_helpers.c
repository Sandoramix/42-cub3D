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
		if (get_map_at(game, game->engine.map_coords.y, game->engine.map_coords.x) == 0 ||
			get_map_at(game, game->engine.map_coords.y, game->engine.map_coords.x) == MAP_WALL)
			game->engine.hit = 1;
	}
}

void get_wall_coords(t_var *game, int x)
{
	if (game->engine.side == CNF_WALL_WEST || game->engine.side == CNF_WALL_EAST)
		game->engine.wall_dist = (game->engine.ray.x - game->engine.delta_dist.x);
	else
		game->engine.wall_dist = (game->engine.ray.y - game->engine.delta_dist.y);
	int wall_height = (int)(game->config.win_height / game->engine.wall_dist);
	game->engine.wall_ceil = -wall_height / 2.0 + game->config.win_height / 2.0 + game->player.offset + ((game->player.pos_z + game->player.head_pos_z) / game->engine.wall_dist);
	game->engine.wall_floor = wall_height / 2.0 + game->config.win_height / 2.0 + game->player.offset + ((game->player.pos_z + game->player.head_pos_z) / game->engine.wall_dist);
	if (game->engine.wall_ceil < 0)
		game->engine.wall_ceil = 0;
	if (game->engine.wall_floor >= game->config.win_height)
		game->engine.wall_floor = game->config.win_height - 1;



/* 	calc_texture(game, x, wall_height);
 */

	double wallX; 
	if (game->engine.side == CNF_WALL_WEST || game->engine.side == CNF_WALL_EAST)
	{
		wallX = game->player.y_px + game->engine.wall_dist * game->engine.dir.y;
	}
	else
	{
		wallX = game->player.x_px + game->engine.wall_dist * game->engine.dir.x;
	}
	wallX -= floor((wallX));

	int texX = (int)(wallX * 64.0);
	if ((game->engine.side == CNF_WALL_WEST || game->engine.side == CNF_WALL_SOUTH))
	{
		texX = 64 - texX - 1;
	}

	double step = 1.0 * 64 / wall_height;
	t_img *texture[4] = {game->config.wall_nord, game->config.wall_east, game->config.wall_west, game->config.wall_south};
	double texPos = (game->engine.wall_ceil - game->config.win_height / 2 + wall_height / 2) * step;

	int z = x;
	for (int y = game->engine.wall_ceil; y <= game->engine.wall_floor; y++)
	{
		int texY = (int)texPos & (64 - 1);
		texPos += step;

		char *pixel = texture[game->engine.side]->data + (texY * texture[game->engine.side]->size_line) + (texX * (texture[game->engine.side]->bpp / 8));
		int color = *(int *)pixel;

		fill_img_buffer(game, z, y, color);
	}
}
