/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_horizontal_event.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 00:54:49 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:40:26 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// LISTENERS--------------------------------------------------------------------
void	movement_h_event_pressed(int keycode, t_var *game)
{
	if (keycode == MOVE_FORWARD)
		game->event.up = true;
	if (keycode == MOVE_BACKWARD)
		game->event.down = true;
	if (keycode == MOVE_RIGHT)
		game->event.right = true;
	if (keycode == MOVE_LEFT)
		game->event.left = true;
	if (keycode == SPRINT)
		game->cnf.speed_mult = 1.5;
}

void	movement_h_event_released(int keycode, t_var *game)
{
	if (keycode == MOVE_FORWARD)
		game->event.up = false;
	if (keycode == MOVE_BACKWARD)
		game->event.down = false;
	if (keycode == MOVE_RIGHT)
		game->event.right = false;
	if (keycode == MOVE_LEFT)
		game->event.left = false;
	if (keycode == SPRINT)
		game->cnf.speed_mult = 1.0;
}

// HANDLERS---------------------------------------------------------------------

static t_dvec2	calc_movement_newpos(t_var *game)
{
	const double	delta_mult = game->cnf.speed_mult
		* game->cnf.speed * game->deltatime;
	const int		dir_y = (int [2]){1, -1}[game->event.up];
	const int		dir_x = (int [2]){-1, 1}[game->event.right];
	t_dvec2		newpos;

	newpos.x = game->player.x;
	newpos.y = game->player.y;
	if (game->event.up || game->event.down)
	{
		newpos.x -= (dir_y * (game->player.dir_x * delta_mult));
		newpos.y -= (dir_y * (game->player.dir_y * delta_mult));
	}
	if (game->event.left || game->event.right)
	{
		newpos.x -= (dir_x * (game->player.dir_y * delta_mult));
		newpos.y += (dir_x * (game->player.dir_x * delta_mult));
	}
	return (newpos);
}

void	handle_horizontal_movement(t_var *game)
{
	const t_dvec2	newpos = calc_movement_newpos(game);
	t_dvec2		temp_pos;

	game->engine.plane.x = -game->player.dir_y * game->cnf.plane_limit;
	game->engine.plane.y = game->player.dir_x * game->cnf.plane_limit;
	temp_pos.x = game->player.x;
	temp_pos.y = game->player.y;
	if (can_player_go_here(game, newpos.x, game->player.y) == OK)
		temp_pos.x = newpos.x;
	if (can_player_go_here(game, temp_pos.x, newpos.y) == OK)
		temp_pos.y = newpos.y;
	set_player_map_dpos(game, temp_pos);
}
