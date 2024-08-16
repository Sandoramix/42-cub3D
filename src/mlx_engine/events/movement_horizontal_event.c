/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_horizontal_event.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 00:54:49 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/16 23:53:47 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// LISTENERS--------------------------------------------------------------------
void	movement_h_event_pressed(int keycode, t_var *game)
{
	if (keycode == KEY_W)
		game->move.up = true;
	if (keycode == KEY_S)
		game->move.down = true;
	if (keycode == KEY_D)
		game->move.right = true;
	if (keycode == KEY_A)
		game->move.left = true;
}
//! #TODO MOVEMENT OSCILLATION
// Do we like it? Yes. Is it a priority? No
//if (game->move.up || game->move.down || game->move.left || game->move.right)
//{
//	game->player.traveled += .35;
//	if (game->player.traveled < 0.0)
//		game->player.traveled = 0.0;
//	game->player.head_pos_z = ((sin(game->player.traveled) + 1.0) / 2) * 169;
//}

void	movement_h_event_released(int keycode, t_var *game)
{
	if (keycode == KEY_W)
		game->move.up = false;
	if (keycode == KEY_S)
		game->move.down = false;
	if (keycode == KEY_D)
		game->move.right = false;
	if (keycode == KEY_A)
		game->move.left = false;
}
// TODO MOVEMENT OSCILLATION
//if (!game->move.up && !game->move.down &&
//	!game->move.left && !game->move.right)
//	game->player.travel_count = 0;

// HANDLERS---------------------------------------------------------------------

static t_dpoint	calc_movement_newpos(t_var *game)
{
	const double	delta_mult = game->config.defaults.speed * game->deltatime;
	const int		dir_y = (int [2]){1, -1}[game->move.up];
	const int		dir_x = (int [2]){-1, 1}[game->move.right];
	t_dpoint		newpos;

	newpos.x = game->player.x;
	newpos.y = game->player.y;
	if (game->move.up || game->move.down)
	{
		newpos.x -= (dir_y * (game->player.dir_x * delta_mult)) / TILE_SIZE;
		newpos.y -= (dir_y * (game->player.dir_y * delta_mult)) / TILE_SIZE;
	}
	if (game->move.left || game->move.right)
	{
		newpos.x -= (dir_x * (game->player.dir_y * delta_mult)) / TILE_SIZE;
		newpos.y += (dir_x * (game->player.dir_x * delta_mult)) / TILE_SIZE;
	}
	return (newpos);
}

void	handle_horizontal_movement(t_var *game)
{
	const t_dpoint	newpos = calc_movement_newpos(game);
	t_dpoint		temp_pos;

	game->engine.plane.x = -game->player.dir_y * game->config.plane_limit;
	game->engine.plane.y = game->player.dir_x * game->config.plane_limit;
	temp_pos.x = game->player.x;
	temp_pos.y = game->player.y;
	if (can_player_go_here(game, newpos.x, game->player.y) == OK)
		temp_pos.x = newpos.x;
	if (can_player_go_here(game, temp_pos.x, newpos.y) == OK)
		temp_pos.y = newpos.y;
	set_player_map_dpos(game, temp_pos);
}
