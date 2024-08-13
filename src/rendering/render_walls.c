/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:57:39 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/12 18:15:45 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// do we need it? Questionable. Is it good? Even more questionable. Did I enjoy writing it? mmmhhhh
t_rgb apply_fog(t_rgb *applyon, double fog_intensity)
{
	t_rgb color;

	color.color.red = (1.0 - (double)fog_intensity) * applyon->color.red + fog_intensity * 1;
	color.color.green = (1.0 - (double)fog_intensity) * applyon->color.green + fog_intensity * 1;
	color.color.blue = (1.0 - (double)fog_intensity) * applyon->color.blue + fog_intensity * 1;

	return (color);
}

t_uint apply_fog_walls(t_rgb *color, double fog_intensity)
{
	const int darkened_red = color->color.red * fog_intensity;
	const int darkened_green = color->color.green * fog_intensity;
	const int darkened_blue = color->color.blue * fog_intensity;
	t_uint darkened_color;

	// Combine the darkened components back into a single color
	darkened_color = (darkened_blue << 16) | (darkened_green << 8) | darkened_red;
	return darkened_color;
}

void render_walls(t_var *game)
{
	float fog_intensity;
	t_rgb color;
	t_texture *tex;
	int x;
	int y;

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
		while (y <= game->config.win_height)
		{
			if (y < game->engine.wall_ceil)
			{
				// do we need it? Questionable. Is it good? Even more questionable. Did I enjoy writing it? mmmhhhh
				fog_intensity = (float)(y) / (game->engine.wall_ceil);
				if (fog_intensity > 1.)
					fog_intensity = 1.;
				draw_px_to_img_rgb(game, x, y, apply_fog(&game->config.ceiling, fog_intensity));
			}
			else if (y >= game->engine.wall_ceil && y < game->engine.wall_floor)
			{
				tex->y = (int)tex->scaled_textpos & (tex->text_array[game->engine.side]->height - 1); // serve a tenerlo in range
				tex->scaled_textpos += tex->scale;
				color = get_texture_color(game);
				fog_intensity = 1.0 - (double)game->engine.wall_dist / 20.0; // Adjust the divisor for effect
				if (fog_intensity < 0)
					fog_intensity = 0; // Ensure it doesn't go below 0
				draw_px_to_img(game, x, y, apply_fog_walls(&color, fog_intensity));
			}
			else
			{
				// do we need it? Questionable. Is it good? Even more questionable. Did I enjoy writing it? mmmhhhh
				fog_intensity = 1.0f - (float)(y - game->engine.wall_floor) / (game->config.win_height - game->engine.wall_floor);
				if (fog_intensity < 0.6)
					fog_intensity = 0.6;
				draw_px_to_img_rgb(game, x, y, apply_fog(&game->config.floor, fog_intensity));
			}
			y++;
		}
		x++;
	}
}
