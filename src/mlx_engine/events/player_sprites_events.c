/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_sprites_events.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:31:29 by rileone           #+#    #+#             */
/*   Updated: 2024/08/17 15:40:41 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	player_sprites_event_pressed(int keycode, t_var *game)
{
	if (keycode == GUARD)
		game->event.block = true;
}

void	player_sprites_event_released(int keycode, t_var *game)
{
	if (keycode == GUARD)
		game->event.block = false;
}

void	handle_player_sprites(t_var *game)
{
	if (game->event.jump || game->event.is_jumping)
	{
		game->cnf.hands_sprites.active = game->cnf.hands_sprites.rest;
		game->cnf.hands_sprites.active_screen_x = game->cnf.window_width
			- game->cnf.hands_sprites.rest->width;
	}
	else if (game->event.block && !game->event.jump)
	{
		game->cnf.hands_sprites.active = game->cnf.hands_sprites.block;
		game->cnf.hands_sprites.active_screen_x = game->cnf.window_width
			/ 2 + game->cnf.hands_sprites.block->width / 2 - 100;
	}
	else
		game->cnf.hands_sprites.active = NULL;
}
