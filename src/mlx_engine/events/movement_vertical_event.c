/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_vertical_event.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:24:30 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 01:40:48 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// LISTENERS--------------------------------------------------------------------

void	movement_v_event_pressed(int keycode, t_var *game)
{
	if (keycode == KEY_W)
		game->move.up = true;
	if (keycode == KEY_S)
		game->move.down = true;
	if (keycode == KEY_D)
		game->move.right = true;
	if (keycode == KEY_A)
		game->move.left = true;
	if (keycode == XK_space && !game->move.jump)
	{
		game->move.jump = true;
		game->move.jump_mult = 1;
	}
	if (keycode == XK_Control_L)
		game->move.crouch = true;
}

void	movement_v_event_released(int keycode, t_var *game)
{
	if (keycode == KEY_W)
		game->move.up = false;
	if (keycode == KEY_S)
		game->move.down = false;
	if (keycode == KEY_D)
		game->move.right = false;
	if (keycode == KEY_A)
		game->move.left = false;
	if (keycode == XK_Control_L)
		game->move.crouch = false;
}

// HANDLERS---------------------------------------------------------------------

static void	squat_event(t_var *game)
{
	if (game->move.crouch && !game->move.has_crouched)
	{
		game->player.head_pos_z = -CROUCH_HEIGHT;
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
	if (game->move.jump && game->move.jump_mult == 1)
	{
		game->player.pos_z += Z_ACCELLERATION * game->deltatime;
		if (game->player.pos_z >= JUMP_LIMIT)
		{
			game->player.pos_z = JUMP_LIMIT;
			game->move.jump_mult = -1;
		}
	}
	if (game->move.jump && game->move.jump_mult == -1)
	{
		game->player.pos_z -= Z_ACCELLERATION * game->deltatime;
		if (game->player.pos_z <= 0)
		{
			game->player.pos_z = 0;
			game->move.jump_mult = 0;
			game->move.jump = false;
		}
	}
	squat_event(game);
}
