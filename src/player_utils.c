/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:10:20 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/04 14:43:43 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	update_player(t_var *game, int x, int y, double angle)
{
	if (!game)
		return ;
	game->player.x = x;
	game->player.y = y;
	game->player.angle = angle;
}

double	chr_player_to_angle(char player_c)
{
	if (player_c == MAP_PLAYER_NORD)
		return (360.0 - 90.0);
	if (player_c == MAP_PLAYER_EAST)
		return (0.0);
	if (player_c == MAP_PLAYER_WEST)
		return (180.0);
	if (player_c == MAP_PLAYER_SOUTH)
		return (90.0);
	return (0.0);
}

bool	chr_is_player(char c)
{
	return (c == MAP_PLAYER_NORD || c == MAP_PLAYER_EAST
		|| c == MAP_PLAYER_WEST || c == MAP_PLAYER_WEST);
}
