/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_crosshair.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 02:11:13 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:24:59 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	render_crosshair(t_var *game)
{
	const int	win_width_half = game->cnf.window_width / 2;
	const int	win_height_half = game->cnf.window_height / 2;
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
