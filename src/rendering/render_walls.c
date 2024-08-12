/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:57:39 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/12 16:36:47 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void render_walls(t_var *game)
{
	int x;
	int y;
	t_texture *tex;

	tex = &game->engine.texture;
	x = 0;
	while (x <= game->config.win_width)
	{
		init_vars(game, x);
		calc_direction(game);
		loop_until_hit_wall(game);
		get_wall_coords(game);
		calc_texture_coords(game);
		y = game->engine.wall_ceil;
		while(y <= game->engine.wall_floor)
		{
			tex->y = (int)tex->scaled_textpos
				& (tex->text_array[game->engine.side]->height - 1); //serve a tenerlo in range
			tex->scaled_textpos += tex->scale;
			draw_px_to_img(game, x, y, get_texture_color(game));
			y++;
		}
		x++;
	}
}
