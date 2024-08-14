/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:55:07 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 02:29:14 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/* TODO It'll maybe come in useful

void draw_line(t_var *game, t_dpoint start, t_dpoint end)
{
	t_dpoint delta;
	t_dpoint increment;
	t_dpoint next_point;
	int pixels;
	int counter;

	delta = (t_dpoint){end.x - start.x, end.y - start.y};
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	increment = (t_dpoint){delta.x / pixels, delta.y / pixels};
	next_point = (t_dpoint){start.x, start.y};
	counter = 0;
	while (counter < pixels)
	{
		draw_pixel(game, (int)next_point.x, (int)next_point.y, 0x0);
		next_point.x += increment.x;
		next_point.y += increment.y;
		counter++;
	}
}

void draw_minimap_rays(t_var *game)
{
	t_dpoint start_px;
	t_dpoint end_px;
	double angle;

	angle = -FOV / 2;
	start_px = (t_dpoint){game->player.x_px + game->engine.plane.x,
		game->player.y_px + game->engine.plane.y};
	while (angle <= FOV / 2)
	{
		end_px = calculate_point(start_px, angle, game->engine.wall_dist);
		draw_line(game, start_px, end_px);
		angle++;
	}
}
*/

static void	render_player(t_var *game)
{
	t_dpoint				playerpos;
	const int				tile_scale = game->config.minimap_scale;
	const int				player_scale = game->config.minimap_player_scale;

	playerpos = (t_dpoint){game->player.x_px / TILE_SIZE * tile_scale,
		game->player.y_px / TILE_SIZE * tile_scale};

	// TODO keep the player in bounds.
	draw_rectangle(game, (t_point){playerpos.x, playerpos.y},
		(t_point){playerpos.x + player_scale, playerpos.y + player_scale},
		0xFF0000);
}

/*
# Minimap rendering

This function will render the minimap onto the window

## TODOLIST
- [ ] Make the minimap of fixed size AxB
- [ ] Put the player at center of the minimap (checkout "the witcher"'s minimap)
	- [ ] If the player is near the map's end
		then the view should stop at the far border and the player would move
		from the center
- [ ] Supposedly it's already needed in points above,
	make space for the minimap's zoom/dezoom
*/
void	render_minimap(t_var *game)
{
	const int				scale = game->config.minimap_scale;
	const unsigned long		colors[2] = {0x333333, game->config.floor.hex};
	int						dx;
	int						dy;

	dy = -1;
	while (++dy < game->mapinfo.rows_mtx)
	{
		dx = -1;
		while (game->mapinfo.map[dy][++dx])
		{
			draw_rectangle_rgb(game,
				(t_point){dx * scale, dy * scale},
				(t_point){dx * scale + scale, dy * scale + scale},
				hex_to_rgba(colors[get_map_at(game, dy, dx) != MAP_WALL]));
		}
	}
	render_player(game);
}
