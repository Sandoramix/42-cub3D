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

static t_dvec2	calculate_player_new_pos(t_var *game)
{
	const double	multiplier = game->cnf.speed
		* game->cnf.speed_mult * game->deltatime;
	const int		dir_y = (int [2]){1, -1}[game->event.up];
	const int		dir_x = (int [2]){-1, 1}[game->event.right];
	t_dvec2			new_pos;

	new_pos.x = game->player.pos.x;
	new_pos.y = game->player.pos.y;
	if (game->event.up || game->event.down)
	{
		new_pos.x -= (dir_y * (game->player.dir.x * multiplier));
		new_pos.y -= (dir_y * (game->player.dir.y * multiplier));
	}
	if (game->event.left || game->event.right)
	{
		new_pos.x -= (dir_x * (game->player.dir.y * multiplier));
		new_pos.y += (dir_x * (game->player.dir.x * multiplier));
	}
	return (new_pos);
}

void	handle_horizontal_movement(t_var *game)
{
	const t_dvec2	new_pos = calculate_player_new_pos(game);
	t_dvec2			updated;

	game->engine.plane.x = -game->player.dir.y * game->cnf.plane_limit;
	game->engine.plane.y = game->player.dir.x * game->cnf.plane_limit;
	updated.x = game->player.pos.x;
	updated.y = game->player.pos.y;
	if (can_player_go_here(game, new_pos.x, updated.y) == OK)
		updated.x = new_pos.x;
	if (can_player_go_here(game, updated.x, new_pos.y) == OK)
		updated.y = new_pos.y;
	update_player_pos(game, updated);
}
