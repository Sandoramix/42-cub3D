/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:48:21 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/13 22:46:14 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	update_hit_texture(t_var *game, bool check_horizontal)
{
	if (check_horizontal)
	{
		if (game->engine.step_x > 0)
		{
			game->engine.side = CNF_WALL_EAST;
			game->engine.texture.hit_texture = game->config.wall_east;
		}
		else
		{
			game->engine.side = CNF_WALL_WEST;
			game->engine.texture.hit_texture = game->config.wall_west;
		}
		return ;
	}
	if (game->engine.step_y > 0)
	{
		game->engine.side = CNF_WALL_NORD;
		game->engine.texture.hit_texture = game->config.wall_nord;
	}
	else
	{
		game->engine.side = CNF_WALL_SOUTH;
		game->engine.texture.hit_texture = game->config.wall_south;
	}
}

static void	increase_raylen(t_var *game, t_raycast *engine)
{
	if (engine->ray.x < engine->ray.y)
	{
		engine->ray.x += engine->delta_dist.x;
		engine->map_coords.x += engine->step_x;
		update_hit_texture(game, true);
	}
	else
	{
		engine->ray.y += engine->delta_dist.y;
		engine->map_coords.y += engine->step_y;
		update_hit_texture(game, false);
	}
	engine->step_count++;
}

void	loop_until_hit_wall(t_var *game)
{
	char	check_res;

	game->engine.ray_hit = false;
	game->engine.side = 0;
	game->engine.step_count = 0;
	while (game->engine.ray_hit == false)
	{
		check_res = get_map_at(game, game->engine.map_coords.y,
				game->engine.map_coords.x);
		increase_raylen(game, &game->engine);
		if (check_res == 0 || check_res == MAP_WALL)
			game->engine.ray_hit = true;
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
	if (game->engine.wall_ceil < 0 || isinf(game->engine.wall_ceil) || isnan(game->engine.wall_ceil))
		game->engine.wall_ceil = 0;
	if (game->engine.wall_floor >= game->config.win_height || isinf(game->engine.wall_floor) || isnan(game->engine.wall_floor))
		game->engine.wall_floor = game->config.win_height - 1;
}
