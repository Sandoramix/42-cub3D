/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:10:20 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:25:30 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_dvec2	set_player_map_dpos(t_var *game, t_dvec2 new_pos)
{
	const double	units = game->cnf.tilesize;

	if (!game)
		return (new_pos);
	game->player.x = new_pos.x;
	game->player.y = new_pos.y;
	game->player.x_px = new_pos.x * units;
	game->player.y_px = new_pos.y * units;
	return (new_pos);
}

void	init_player(t_var *game, int x, int y, t_ivec2 direction)
{
	const double	units = game->cnf.tilesize;

	if (!game)
		return ;
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	game->player.x_px = x * units + units / 2;
	game->player.y_px = y * units + units / 2;
	game->player.dir_y = direction.y;
	game->player.dir_x = direction.x;
}

t_ivec2	chr_player_to_direction(char player_c)
{
	if (player_c == TILE_PLAYER_NORD)
		return ((t_ivec2){0, -1});
	if (player_c == TILE_PLAYER_EAST)
		return ((t_ivec2){1, 0});
	if (player_c == TILE_PLAYER_WEST)
		return ((t_ivec2){-1, 0});
	if (player_c == TILE_PLAYER_SOUTH)
		return ((t_ivec2){0, 1});
	return ((t_ivec2){0, 0});
}

bool	chr_is_player(char c)
{
	return (c == TILE_PLAYER_NORD || c == TILE_PLAYER_EAST
			|| c == TILE_PLAYER_WEST || c == TILE_PLAYER_SOUTH);
}
