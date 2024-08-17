/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_vertical_event.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:24:30 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:40:39 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// LISTENERS--------------------------------------------------------------------

void	movement_v_event_pressed(int keycode, t_var *game)
{
	if (keycode == MOVE_FORWARD)
		game->event.up = true;
	if (keycode == MOVE_BACKWARD)
		game->event.down = true;
	if (keycode == MOVE_RIGHT)
		game->event.right = true;
	if (keycode == MOVE_LEFT)
		game->event.left = true;
	if (keycode == JUMP && !game->event.is_jumping)
	{
		game->event.jump = true;
		game->event.is_jumping = true;
		game->event.jump_mult = 1;
	}
	if (keycode == SQUAT)
		game->event.crouch = true;
}

void	movement_v_event_released(int keycode, t_var *game)
{
	if (keycode == MOVE_FORWARD)
		game->event.up = false;
	if (keycode == MOVE_BACKWARD)
		game->event.down = false;
	if (keycode == MOVE_RIGHT)
		game->event.right = false;
	if (keycode == MOVE_LEFT)
		game->event.left = false;
	if (keycode == SQUAT)
		game->event.crouch = false;
	if (keycode == JUMP)
		game->event.jump = false;
}

// HANDLERS---------------------------------------------------------------------

static void	squat_event(t_var *game)
{
	if (game->event.crouch && !game->event.has_crouched)
	{
		game->player.head_pos_z = -game->cnf.squat_offset;
		game->event.has_crouched = true;
	}
	if (!game->event.crouch && game->event.has_crouched)
	{
		game->player.head_pos_z = 0;
		game->event.has_crouched = false;
	}
}

/**
 * pos z per il momento e' sempre zero
 * serve a gestire la posizione del player sull asse z
 * devo solo implementare il keyhook a questo punto
 */
void	handle_vertical_movement(t_var *game)
{
	const double	jumplimit = game->cnf.jump_limit;
	const double	jumpforce = game->cnf.jump_force;

	if (game->event.is_jumping && game->event.jump_mult == 1)
	{
		game->player.pos_z += jumpforce * game->deltatime;
		if (game->player.pos_z >= jumplimit)
		{
			game->player.pos_z = jumplimit;
			game->event.jump_mult = -1;
		}
	}
	else if (game->event.is_jumping && game->event.jump_mult == -1)
	{
		game->player.pos_z -= jumpforce * game->deltatime;
		if (game->player.pos_z <= 0)
		{
			game->player.pos_z = 0;
			game->event.jump_mult = 0;
			game->event.is_jumping = false;
		}
	}
	squat_event(game);
}
