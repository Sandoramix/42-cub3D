/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement_event.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:04:32 by rileone           #+#    #+#             */
/*   Updated: 2024/08/17 16:59:46 by rileone          ###   ########.fr       */
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
	}
	else if (diff > 0)
	{
		game->event.mouse_up = false;
		game->event.mouse_down = true;
	}
	else
	{
		game->event.mouse_up = false;
		game->event.mouse_down = false;
	}
}

void	choose_mouse_direction_x(t_var *game, int diff)
{
	if (diff > 0)
	{
		game->event.mouse_right = true;
		game->event.mouse_left = false;
	}
	else if (diff < 0)
	{
		game->event.mouse_left = true;
		game->event.mouse_right = false;
	}
	else
	{
		game->event.mouse_left = false;
		game->event.mouse_right = false;
	}
}

void	handle_mouse_offscreen(t_var *game, t_mouse *mouse, int diff)
{
	(void)diff;
	if (mouse->pos.x < 100 || mouse->pos.x > game->cnf.window_width - 100)
	{
		mlx_mouse_move(game->mlx, game->mlx_win,
			game->cnf.window_width / 2, game->cnf.window_height / 2);
		mouse->pos.x = game->cnf.window_width / 2;
		mouse->pos.y = game->cnf.window_height / 2;
	}
}

void	handle_mouse_rotation(t_var *game, t_mouse *mouse)
{
	const t_point prev = {mouse->pos.x,  mouse->pos.y};
	int diff;

	mlx_mouse_get_pos(game->mlx, game->mlx_win, &mouse->pos.x, &mouse->pos.y);
	if (is_mouse_inside_screen(game, mouse))
	{
		mlx_mouse_hide(game->mlx, game->mlx_win);
		diff = mouse->pos.x - prev.x;
		choose_mouse_direction_x(game, diff);
		diff = mouse->pos.y - prev.y;
		choose_mouse_direction_y(game, diff);

		//TODO improve offscreen checks
			//-ho provato a controllare quanto grande fosse la diff
			//per far si che quando c era un movimento di mouse troppo grande il
			//cursore venisse riportato al centro FAIL
		//handle_mouse_offscreen(game, mouse, diff);
	}
	else
	{
		game->event.mouse_left = false;
		game->event.mouse_right = false;
		mlx_mouse_show(game->mlx, game->mlx_win);
	}
}
