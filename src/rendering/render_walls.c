/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:57:39 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/12 18:12:25 by odudniak         ###   ########.fr       */
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
		y = 0;
		while(y <= game->config.win_height)
		{
			if(y < game->engine.wall_ceil)
				draw_px_to_img(game, x, y, (t_rgb){game->config.ceiling.hex});
			else if(y >= game->engine.wall_ceil && y < game->engine.wall_floor)
			{
				tex->y = (int)tex->scaled_textpos
				& (tex->text_array[game->engine.side]->height - 1); //serve a tenerlo in range
				tex->scaled_textpos += tex->scale;
				draw_px_to_img(game, x, y, ((t_rgb){get_texture_color(game)}));
			}
			else
				draw_px_to_img(game, x, y, (t_rgb){game->config.floor.hex});
			y++;
		}
		x++;
	}
}
