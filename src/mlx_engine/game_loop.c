/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:29:26 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/19 15:25:16 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	game_loop(t_var *game)
{
	delta_time(game, false);
	handle_vertical_movement(game);
	handle_horizontal_movement(game);
	handle_horizontal_rotation(game);
	handle_vertical_rotation(game);
	if (WITH_BONUS)
	{
		handle_player_sprites(game);
		handle_mouse_rotation(game);
	}
	render_base(game);
	if (WITH_BONUS)
	{
		render_crosshair(game);
		render_minimap(game);
		render_sprites(game, &game->cnf.hands_sprites);
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->frame, 0, 0);
	return (1);
}
