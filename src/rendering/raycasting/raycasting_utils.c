/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:48:21 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:38:06 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		increase_raylen(&game->engine, &game->cnf);
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
void	get_wall_coords(t_var *game, t_raycast *eng, t_wall *wall)
{
	t_player	*ply;
	double		z_offset;
	int			half_wall;
	int			half_win_h;

	ply = &game->player;
	half_win_h = game->cnf.window_height / 2;
	if (eng->side == CNF_WALL_WEST || eng->side == CNF_WALL_EAST)
		wall->dist = (eng->ray.x - eng->delta_dist.x);
	else
		wall->dist = (eng->ray.y - eng->delta_dist.y);
	z_offset = ply->offset + ((ply->pos_z + ply->head_pos_z) / wall->dist);
	wall->height = (int)(game->cnf.window_height / wall->dist);
	half_wall = wall->height / 2;
	wall->ceil = -half_wall + half_win_h + z_offset;
	wall->floor = half_wall + half_win_h + z_offset;
	wall->ceil = int_imax(0, wall->ceil);
	wall->floor = int_imin(game->cnf.window_height - 1, wall->floor);
}
