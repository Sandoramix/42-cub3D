/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:29:26 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/27 04:54:44 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	game_loop(t_var *game)
{
	delta_time(game, false);
	handle_mouse_rotation(game);
	handle_vertical_movement(game);
	handle_horizontal_movement(game);
	handle_horizontal_rotation(game);
	handle_vertical_rotation(game);
	render_raycast(game);
	render_minimap(game);
	render_extra_sprites(game, &game->cnf.hands_sprites);
	render_crosshair(game);
	handle_player_sprites(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->frame, 0, 0);
	game_info_layout(game);
	debug_info(game);
	return (1);
}
