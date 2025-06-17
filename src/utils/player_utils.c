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

t_dvec2	update_player_pos(t_var *game, t_dvec2 new_pos)
{
	if (!game)
		return (new_pos);
	game->player.pos.x = new_pos.x;
	game->player.pos.y = new_pos.y;
	return (new_pos);
}

void	init_player(t_var *game, int x, int y)
{
	if (!game)
		return ;
	game->player.pos.x = x + 0.5;
	game->player.pos.y = y + 0.5;
	game->player.dir = get_player_direction(get_map_at(game, y, x));
}

t_dvec2	get_player_direction(char player_c)
{
	if (player_c == TILE_PLAYER_NORD)
		return ((t_dvec2){0, -1});
	if (player_c == TILE_PLAYER_EAST)
		return ((t_dvec2){1, 0});
	if (player_c == TILE_PLAYER_WEST)
		return ((t_dvec2){-1, 0});
	if (player_c == TILE_PLAYER_SOUTH)
		return ((t_dvec2){0, 1});
	return ((t_dvec2){0, 0});
}

bool	chr_is_player(char c)
{
	return (c == TILE_PLAYER_NORD || c == TILE_PLAYER_EAST
		|| c == TILE_PLAYER_WEST || c == TILE_PLAYER_SOUTH);
}
