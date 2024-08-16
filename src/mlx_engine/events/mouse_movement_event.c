/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement_event.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:04:32 by rileone           #+#    #+#             */
/*   Updated: 2024/08/16 15:20:13 by rileone          ###   ########.fr       */
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
	if(x < 0 || y < 0 || x > game->config.win_width || y > game->config.win_height)
		game->mouse.inside_screen = false;
	else
		game->mouse.inside_screen = true;
	return (OK);
}


int is_mouse_inside_screen(t_var *game, t_mouse *mouse)
{
	return (mouse->pos.x > 0 && mouse->pos.y > 0
		&& mouse->pos.x < game->config.win_width
		&& mouse->pos.y < game->config.win_height);	
}

#define MOUSE_CENTER_TOLERANCE 200

int is_mouse_left(t_var *game, t_mouse *mouse)
{
	return (mouse->pos.x < game->config.win_width / 2 - MOUSE_CENTER_TOLERANCE / 2);
}

int is_mouse_right(t_var *game, t_mouse *mouse)
{
	return (mouse->pos.x > game->config.win_width / 2 + MOUSE_CENTER_TOLERANCE / 2);
}

int is_mouse_centered(t_var *game, t_mouse *mouse)
{
	return (!is_mouse_left(game, mouse) && !is_mouse_right(game, mouse));
}

void handle_mouse_rotation(t_var *game, t_mouse *mouse)
{
	mlx_mouse_get_pos(game->mlx, game->mlx_win,
		&mouse->pos.x, &mouse->pos.y);
	if (!is_mouse_inside_screen(game, mouse))
	{
		game->mouse.inside_screen = false;
		game->move.rot_left = false;
		game->move.rot_right = false;
		mlx_mouse_show(game->mlx, game->mlx_win);
	}
	else
	{
		//TODO : i need to detach the mouse rotation from the keys rotation
		//TODO : add rotation speed based on distance from screen center
		//TODO : decide if i want to keep the mouse inside the screen when playing
		game->mouse.inside_screen = true;
		mlx_mouse_hide(game->mlx, game->mlx_win);
		if(is_mouse_centered(game, mouse))
		{
			game->move.rot_left = false;
			game->move.rot_right = false;
		}
		if(is_mouse_left(game, mouse))
		{
			game->move.rot_left = true;
			game->move.rot_right = false;
			mlx_mouse_move(game->mlx, game->mlx_win,
				game->config.win_width / 2, game->config.win_height / 2);
		}
		if(is_mouse_right(game, mouse))
		{
			game->move.rot_right = true;
			game->move.rot_left = false;
			mlx_mouse_move(game->mlx, game->mlx_win,
				game->config.win_width / 2, game->config.win_height / 2);
		}
	}
}