/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:48:21 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/11 23:48:29 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


void get_wall_coords(t_var *game)
{
	int half_wall;
	int half_win_h;

	half_win_h = game->config.win_height / 2.0;
	if (game->engine.side == CNF_WALL_WEST || game->engine.side == CNF_WALL_EAST)
		game->engine.wall_dist = (game->engine.ray.x - game->engine.delta_dist.x);
	else
		game->engine.wall_dist = (game->engine.ray.y - game->engine.delta_dist.y);
	game->engine.wall_height = (int)(game->config.win_height / game->engine.wall_dist);
	half_wall = game->engine.wall_height / 2.0;
	game->engine.wall_ceil = -half_wall + half_win_h + game->player.offset + ((game->player.pos_z + game->player.head_pos_z) / game->engine.wall_dist);
	game->engine.wall_floor = half_wall + half_win_h + game->player.offset + ((game->player.pos_z + game->player.head_pos_z) / game->engine.wall_dist);
	if (game->engine.wall_ceil < 0)
		game->engine.wall_ceil = 0;
	if (game->engine.wall_floor >= game->config.win_height)
		game->engine.wall_floor = game->config.win_height - 1;
}
