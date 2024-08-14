/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:57:39 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 02:03:35 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Draw floor and ceiling vertical strips per each x coordinate.
 * This should be faster instead of doing 2 rectangles of a half screen sizes.
 * @param game game obj
 * @param x window x coordinate where to put the strips.
 */
static	void	render_floor_n_ceiling(t_var *game, int x)
{
	const t_point	ceiling_start = (t_point){x, 0};
	const t_point	ceiling_end = (t_point){x, game->engine.wall_ceil};
	const t_point	floor_start = (t_point){x, game->engine.wall_floor};
	const t_point	floor_end = (t_point){x, game->config.win_height};

	draw_rectangle_rgb(game, ceiling_start, ceiling_end, game->config.ceiling);
	draw_rectangle_rgb(game, floor_start, floor_end, game->config.floor);
}



void	render_base(t_var *game)
{
	int x;
	int y;
	int tex_x;
	int tex_y;

	x = -1;
	while (++x <= game->config.win_width)
	{
		init_vars(game, x);
		calc_direction(game);
		loop_until_hit_wall(game);
		get_wall_coords(game);
		render_floor_n_ceiling(game, x);
		tex_x = calc_text_x(game);
		calc_scaled_textpos(game, &game->engine, &game->player);
		y = game->engine.wall_ceil - 1;
		while (++y < game->engine.wall_floor)
		{
			tex_y = calc_text_y(game);
			game->engine.texture.scaled_textpos += game->engine.texture.scale;
			draw_pixel_rgb(game, x, y, get_texture_color(game, tex_x, tex_y));
		}
	}
}
