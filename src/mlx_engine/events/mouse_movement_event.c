/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement_event.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:04:32 by rileone           #+#    #+#             */
/*   Updated: 2024/08/15 14:16:45 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	on_mousemovement(int keycode, t_var *game)
{
	(void)keycode;/*se il muose fuori dallo schermo*/
	if (!mlx_mouse_get_pos(game->mlx, game->mlx_win,
			&game->mouse.pos.x, &game->mouse.pos.y)) 
		game->mouse.inside_screen = false;
	game->mouse.inside_screen = true;
}
