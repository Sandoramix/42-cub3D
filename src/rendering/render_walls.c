/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:57:39 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/13 21:31:44 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	void	draw_floor_n_ceiling(t_var *game, int x)
{
	const t_point	ceiling_start = (t_point){x, 0};
	const t_point	ceiling_end = (t_point){x, game->engine.wall_ceil};
	const t_point	floor_start = (t_point){x, game->engine.wall_floor};
	const t_point	floor_end = (t_point){x, game->config.win_height};

	draw_rectangle_rgb(game, ceiling_start, ceiling_end, game->config.ceiling);
	draw_rectangle_rgb(game, floor_start, floor_end, game->config.floor);
}

void	render_walls(t_var *game)
{
	t_texture	*tex;
	int			x;
	int			y;

	tex = &game->engine.texture;
	x = -1;
	while (++x <= game->config.win_width)
	{
		init_vars(game, x);
		calc_direction(game);
		loop_until_hit_wall(game);
		get_wall_coords(game);
		calc_texture_coords(game);
		draw_floor_n_ceiling(game, x);
		y = game->engine.wall_ceil - 1;
		while (++y < game->engine.wall_floor)
		{
			tex->y = (int)tex->scaled_textpos
				& (tex->text_array[game->engine.side]->height - 1);
			tex->scaled_textpos += tex->scale;
			draw_px_to_img_rgb(game, x, y, get_texture_color(game));
		}
	}
}
