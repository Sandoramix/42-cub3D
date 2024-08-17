/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement_event.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:04:32 by rileone           #+#    #+#             */
/*   Updated: 2024/08/17 19:55:18 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	on_mouse_click(int button, int x,int y, void *param)
{
	t_var	*game;

	game = (t_var *)param;
	(void)button;
	(void)x;
	(void)y;
	(void)game;
	return (OK);
}

int	is_mouse_inside_screen(t_var *game, t_mouse *mouse)
{
	return (mouse->pos.x > 0 && mouse->pos.y > 0
		&& mouse->pos.x < game->cnf.window_width
		&& mouse->pos.y < game->cnf.window_height);
}

void	choose_mouse_direction_y(t_var *game, int diff)
{
	
	if (diff < 0)
	{
		game->event.mouse_up = true;
		game->event.mouse_down = false;
		game->cnf.rot_vertical_speed = abs(diff) * game->cnf.max_vertical_speed * game->deltatime;
	}
	else if (diff > 0)
	{
		game->event.mouse_up = false;
		game->event.mouse_down = true;
		game->cnf.rot_vertical_speed = abs(diff) * game->cnf.max_vertical_speed * game->deltatime;
	}
	else
	{
		game->event.mouse_up = false;
		game->event.mouse_down = false;
	}
	if (game->cnf.rot_vertical_speed > game->cnf.max_vertical_speed)
			game->cnf.rot_vertical_speed = game->cnf.max_vertical_speed;
}

void	choose_mouse_direction_x(t_var *game, int diff)
{
	if (diff > 0)
	{
		game->event.mouse_right = true;
		game->event.mouse_left = false;
		game->cnf.rot_lateral_speed = abs(diff) * game->deltatime;

	}
	else if (diff < 0)
	{
		game->event.mouse_left = true;
		game->event.mouse_right = false;
		game->cnf.rot_lateral_speed = abs(diff) * game->deltatime;
	}
	else
	{
		game->event.mouse_left = false;
		game->event.mouse_right = false;
	}
	if (game->cnf.rot_lateral_speed > game->cnf.max_lateral_speed)
			game->cnf.rot_lateral_speed = game->cnf.max_lateral_speed;
}

void	handle_mouse_offscreen(t_var *game, t_mouse *mouse, int diff)
{
	//TODO implement
	(void)diff;
	(void)mouse;
	(void)game;
}

void	handle_mouse_rotation(t_var *game, t_mouse *mouse)
{
	const t_point prev = {mouse->pos.x,  mouse->pos.y};
	int treshold = 3;
	t_dpoint diff;

	diff.x = mouse->pos.x - prev.x;
	diff.y = mouse->pos.y - prev.y;
	if(diff.x == 0 && diff.y == 0)
		return;
	mlx_mouse_get_pos(game->mlx, game->mlx_win, &mouse->pos.x, &mouse->pos.y);
	if (is_mouse_inside_screen(game, mouse))
	{
		mlx_mouse_hide(game->mlx, game->mlx_win);
		if(abs(diff.x) > treshold)
			choose_mouse_direction_x(game, diff.x);
		if(abs(diff.y) > treshold)
			choose_mouse_direction_y(game, diff.y);
		//handle_mouse_offscreen(game, mouse, diff);
	}
	else
	{
		mlx_mouse_show(game->mlx, game->mlx_win);
		memset(&game->event.mouse_left, 0, sizeof(bool) * 4); //TODO risky? solo per norminette ma 
														      //se qualcuno in futuro aggiunge direzioni puo essere risky damn 
	}
}
