/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:29:26 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/13 23:53:39 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/**
 * @brief Tunnable crosshair, just need to change `cross_thickness`
 * and `cross_length`
 * @param game game obj
 */
static void	render_crosshair(t_var *game)
{
	const int	win_width_half = game->config.win_width / 2;
	const int	win_height_half = game->config.win_height / 2;
	const int	cross_thickness = 2;
	const int	cross_length = 16;

	draw_rectangle(game, (t_point){win_width_half - cross_thickness / 2,
		win_height_half - cross_length / 2},
		(t_point){win_width_half + cross_thickness / 2,
		win_height_half + cross_length / 2}, 0xffff00);
	draw_rectangle(game, (t_point){win_width_half - cross_length / 2,
		win_height_half - cross_thickness / 2},
		(t_point){win_width_half + cross_length / 2,
		win_height_half + cross_thickness / 2}, 0xffff00);
}



int	game_loop(t_var *game)
{
	delta_time(game, false);
	handle_player_movement(game);
	handle_player_rotation(game);
	//render_background(game);
	render_base(game);
	render_minimap(game);
	render_sprites(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	if(DEBUG)
		debug_info(game);
	render_crosshair(game);
	return (1);
}
