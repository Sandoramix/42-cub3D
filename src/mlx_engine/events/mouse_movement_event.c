/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement_event.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:04:32 by rileone           #+#    #+#             */
/*   Updated: 2024/08/18 15:00:10 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	choose_mouse_direction_x(t_var *game, int diff)
{
	game->event.mouse_rot_left = false;
	game->event.mouse_rot_right = false;
	if (diff > 0)
		game->event.mouse_rot_right = true;
	else if (diff < 0)
		game->event.mouse_rot_left = true;
}

void	handle_mouse_rotation(t_var *game)
{
	const t_ivec2	prev = {game->mousepos.x, game->mousepos.y};
	t_dvec2			diff;

	mlx_mouse_get_pos(game->mlx, game->mlx_win,
		&game->mousepos.x, &game->mousepos.y);
	diff.x = game->mousepos.x - prev.x;
	diff.y = game->mousepos.y - prev.y;
	game->event.mouse_rot_left = false;
	game->event.mouse_rot_right = false;
	if (diff.x == 0)
		return ;
	if (is_mouse_inside_frame(game))
	{
		choose_mouse_direction_x(game, diff.x);
		return ;
	}
}
