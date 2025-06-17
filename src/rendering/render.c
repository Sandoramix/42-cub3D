/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:57:39 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/18 15:27:13 by odudniak         ###   ########.fr       */
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
	const t_ivec2	ceiling_start = (t_ivec2){x, 0};
	const t_ivec2	ceiling_end = (t_ivec2){x, game->engine.wall.ceil};
	const t_ivec2	floor_start = (t_ivec2){x, game->engine.wall.floor};
	const t_ivec2	floor_end = (t_ivec2){x, game->cnf.window_height};

	draw_rectangle_rgb(game, ceiling_start, ceiling_end, game->cnf.ceiling);
	draw_rectangle_rgb(game, floor_start, floor_end, game->cnf.floor);
}

static t_rgba	faded_texture(t_var *game, t_ivec2 texture_coord)
{
	t_rgba	rgba;
	float	fade;

	rgba = get_texture_color(game, texture_coord.x, texture_coord.y);
	fade = 1.0f - (float)game->engine.step_count
		/ (float)game->cnf.max_raycast_steps;
	if (fade < 0.0f)
		fade = 0.0f;
	rgba.red = (t_uchar)((float)rgba.red * fade);
	rgba.green = (t_uchar)((float)rgba.green * fade);
	rgba.blue = (t_uchar)((float)rgba.blue * fade);
	return (rgba);
}

void	render_base(t_var *game)
{
	int		x;
	int		y;
	t_ivec2	texture_coord;

	x = -1;
	while (++x <= game->cnf.window_width)
	{
		init_raycast_vars(game, &game->engine, &game->player, x);
		calc_direction(&game->engine, &game->player);
		loop_until_hit_wall(game);
		get_wall_coords(game, &game->engine, &game->engine.wall);
		render_floor_n_ceiling(game, x);
		texture_coord.x = calc_text_x(game);
		calc_scaled_textpos(game, &game->engine, &game->player);
		y = game->engine.wall.ceil - 1;
		while (++y < game->engine.wall.floor)
		{
			texture_coord.y = calc_text_y(game);
			game->engine.texture.scaled_textpos += game->engine.texture.scale;
			draw_pixel_rgb(game, x, y, faded_texture(game, texture_coord));
		}
	}
}
