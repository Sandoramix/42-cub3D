/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:48:21 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 02:15:13 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}
int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

static void	pick_texture(t_raycast *engine, t_config *cnf, bool horizontal)
{
	if (horizontal)
	{
		if (engine->step_x > 0)
		{
			engine->side = CNF_WALL_EAST;
			engine->texture.hit_texture = cnf->wall_east;
		}
		else
		{
			engine->side = CNF_WALL_WEST;
			engine->texture.hit_texture = cnf->wall_west;
		}
		return ;
	}
	if (engine->step_y > 0)
	{
		engine->side = CNF_WALL_NORD;
		engine->texture.hit_texture = cnf->wall_nord;
	}
	else
	{
		engine->side = CNF_WALL_SOUTH;
		engine->texture.hit_texture = cnf->wall_south;
	}
}

static void	increase_raylen(t_raycast *engine, t_config *cnf)
{
	if (engine->ray.x < engine->ray.y)
	{
		engine->ray.x += engine->delta_dist.x;
		engine->map_coords.x += engine->step_x;
		pick_texture(engine, cnf, true);
	}
	else
	{
		engine->ray.y += engine->delta_dist.y;
		engine->map_coords.y += engine->step_y;
		pick_texture(engine, cnf, false);
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
		increase_raylen(&game->engine, &game->config);
		check_res = get_map_at(game, game->engine.map_coords.y,
				game->engine.map_coords.x);
		if (check_res == 0 || check_res == MAP_WALL)
			game->engine.ray_hit = true;
	}
}

/**
 * @brief Pray and spray function, still unknown to human beings.
 *
 * ### TODO README: this is one of the sources of our problems.
 * @note Only god knows what's happening here.
 * @param game game struct.
 * @bug somebody help
 */
void	get_wall_coords(t_var *game)
{
	double z_offset;
	int	half_wall;
	int	half_win_h;
	

	half_win_h = game->config.win_height / 2;
	if (game->engine.side == CNF_WALL_WEST || game->engine.side == CNF_WALL_EAST)
		game->engine.wall.dist = (game->engine.ray.x - game->engine.delta_dist.x);
	else
		game->engine.wall.dist = (game->engine.ray.y - game->engine.delta_dist.y);
	
	z_offset = game->player.offset + ((game->player.pos_z + game->player.head_pos_z) / game->engine.wall.dist);
	game->engine.wall.height = (int)(game->config.win_height / game->engine.wall.dist);
	half_wall = game->engine.wall.height / 2;
	game->engine.wall.ceil = -half_wall + half_win_h + z_offset;
	game->engine.wall.floor = half_wall + half_win_h + z_offset;
	game->engine.wall.ceil = max(0, game->engine.wall.ceil);
	game->engine.wall.floor = min(game->config.win_height - 1, game->engine.wall.floor);
}
