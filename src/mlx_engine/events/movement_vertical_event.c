/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_vertical_event.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:24:30 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 01:03:23 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// LISTENERS--------------------------------------------------------------------

void	movement_v_event_pressed(int keycode, t_var *game)
{
	if (keycode == MOVE_FORWARD)
		game->move.up = true;
	if (keycode == MOVE_BACKWARD)
		game->move.down = true;
	if (keycode == MOVE_RIGHT)
		game->move.right = true;
	if (keycode == MOVE_LEFT)
		game->move.left = true;
	if (keycode == JUMP && !game->move.is_jumping)
	{
		game->move.jump = true;
		game->move.is_jumping = true;
		game->move.jump_mult = 1;
	}
	if (keycode == SQUAT)
		game->move.crouch = true;
}

void	movement_v_event_released(int keycode, t_var *game)
{
	if (keycode == MOVE_FORWARD)
		game->move.up = false;
	if (keycode == MOVE_BACKWARD)
		game->move.down = false;
	if (keycode == MOVE_RIGHT)
		game->move.right = false;
	if (keycode == MOVE_LEFT)
		game->move.left = false;
	if (keycode == SQUAT)
		game->move.crouch = false;
	if (keycode == JUMP)
		game->move.jump = false;
}

// HANDLERS---------------------------------------------------------------------

static void	squat_event(t_var *game)
{
	if (game->move.crouch && !game->move.has_crouched)
	{
		game->player.head_pos_z = -game->config.defaults.squat_offset;
		game->move.has_crouched = true;
	}
	if (!game->move.crouch && game->move.has_crouched)
	{
		game->player.head_pos_z = 0;
		game->move.has_crouched = false;
	}
}

/**
 * pos z per il momento e' sempre zero
 * serve a gestire la posizione del player sull asse z
 * devo solo implementare il keyhook a questo punto
 */
void	handle_vertical_movement(t_var *game)
{
	const double	jumplimit = game->config.defaults.jump_limit;
	const double	jumpforce = game->config.defaults.jump_force;

	if (game->move.is_jumping && game->move.jump_mult == 1)
	{
		game->player.pos_z += jumpforce * game->deltatime;
		if (game->player.pos_z >= jumplimit)
		{
			game->player.pos_z = jumplimit;
			game->move.jump_mult = -1;
		}
	}
	else if (game->move.is_jumping && game->move.jump_mult == -1)
	{
		game->player.pos_z -= jumpforce * game->deltatime;
		if (game->player.pos_z <= 0)
		{
			game->player.pos_z = 0;
			game->move.jump_mult = 0;
			game->move.is_jumping = false;
		}
	}
	squat_event(game);
}
