/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:10:20 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/09 15:53:26 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	update_player(t_var *game, int x, int y, t_point angle)
{
	if (!game)
		return ;
	game->player.x = x;
	game->player.y = y;
	game->player.x_px = x * TILE_SIZE + TILE_SIZE / 2;
	game->player.y_px = y * TILE_SIZE + TILE_SIZE / 2;
	game->player.dir_y = angle.y;
	game->player.dir_x = angle.x;
	//printf("game->player.dir_y, game->player.dir_x: %f, %f\n", game->player.dir_y, game->player.dir_x);
}

t_point	chr_player_to_angle(char player_c)
{
	if (player_c == MAP_PLAYER_EAST)
		return ((t_point){0, 1});  // East is down
	if (player_c == MAP_PLAYER_NORD)
		return ((t_point){1, 0});  // North is right
	if (player_c == MAP_PLAYER_WEST)
		return ((t_point){0, -1}); // West is up
	if (player_c == MAP_PLAYER_SOUTH)
		return ((t_point){-1, 0}); // South is left
	return ((t_point){0, 0});
}

bool	chr_is_player(char c)
{
	return (c == MAP_PLAYER_NORD || c == MAP_PLAYER_EAST
		|| c == MAP_PLAYER_WEST || c == MAP_PLAYER_SOUTH);
}
