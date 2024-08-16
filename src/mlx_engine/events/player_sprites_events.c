/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_sprites_events.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:31:29 by rileone           #+#    #+#             */
/*   Updated: 2024/08/17 00:18:18 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	player_sprites_event_pressed(int keycode, t_var *game)
{
	if (keycode == XK_Control_R)
		game->move.block = true;
}

void	player_sprites_event_released(int keycode, t_var *game)
{
	if (keycode == XK_Control_R)
		game->move.block = false;
}

void	handle_player_sprites(t_var *game)
{
	if (game->move.jump || game->move.is_jumping)
	{
		game->config.hands_sprites.slctd = game->config.hands_sprites.rest;
		game->config.hands_sprites.slctd_screen_x = game->config.win_width
			- game->config.hands_sprites.rest->width;
	}
	else if (game->move.block && !game->move.jump)
	{
		game->config.hands_sprites.slctd = game->config.hands_sprites.block;
		game->config.hands_sprites.slctd_screen_x = game->config.win_width
			/ 2 + game->config.hands_sprites.block->width / 2 - 100;
	}
	else
		game->config.hands_sprites.slctd = NULL;
}
