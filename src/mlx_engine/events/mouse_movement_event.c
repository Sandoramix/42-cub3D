/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement_event.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:04:32 by rileone           #+#    #+#             */
/*   Updated: 2024/08/15 15:55:28 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int on_mouse_click(int button, int x,int y, void *param)
{
	t_var *game;
	
	game = (t_var *)param;
	(void)button;
	(void)x;
	(void)y;
	//printf("Mouse position: %d %d\n", x, y);
	if(x < 0 || y < 0 || x > game->config.win_width || y > game->config.win_height)
		game->mouse.inside_screen = false;
	else
		game->mouse.inside_screen = true;
	return (OK);
}


void handle_mouse_rotation(t_var *game, t_mouse *mouse)
{
	mlx_mouse_get_pos(game->mlx, game->mlx_win,
		&mouse->pos.x, &mouse->pos.y);
}