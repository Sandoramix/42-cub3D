/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement_event.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:04:32 by rileone           #+#    #+#             */
/*   Updated: 2024/08/15 15:45:24 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int on_mousemovement(int button, int x,int y, void *param)
{
	t_var *game;

	game = (t_var *)param;
	(void)button;
	(void)x;
	(void)y;
	printf("Mouse position: %d %d\n", x, y);
	game->mouse.inside_screen = true;
	return (OK);
}


void handle_mouse_rotation(t_var *game, t_mouse *mouse)
{
	(void)game;
	(void)mouse;
}