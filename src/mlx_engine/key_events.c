/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:12:22 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/18 15:15:39 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	on_keypress(int keycode, t_var *game)
{
	if (keycode == ESC_KEY)
		return (cleanup(game, true, 0), OK);
	camera_h_event_pressed(keycode, game);
	camera_v_event_pressed(keycode, game);
	movement_h_event_pressed(keycode, game);
	movement_v_event_pressed(keycode, game);
	player_sprites_event_pressed(keycode, game);
	return (keycode);
}

int	on_keyrelease(int keycode, t_var *game)
{
	camera_h_event_released(keycode, game);
	camera_v_event_released(keycode, game);
	movement_h_event_released(keycode, game);
	movement_v_event_released(keycode, game);
	player_sprites_event_released(keycode, game);
	if (keycode == MINIMAP_ZOOM_IN
		&& game->cnf.minimap_zoom + .5 <= game->cnf.minimap_zoom_max)
		game->cnf.minimap_zoom += .5;
	if (keycode == MINIMAP_ZOOM_OUT
		&& game->cnf.minimap_zoom - .5 >= game->cnf.minimap_zoom_min)
		game->cnf.minimap_zoom -= .5;
	if (keycode == XK_i || keycode == XK_I)
		game->event.debug = !game->event.debug;
	return (keycode);
}
