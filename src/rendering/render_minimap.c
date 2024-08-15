/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:55:07 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/15 16:31:59 by odudniak         ###   ########.fr       */
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
		end_px = calculate_point(start_px, angle, game->engine.wall.dist);
		draw_line(game, start_px, end_px);
		angle++;
	}
}
*/

void	draw_player(t_var *game, t_point pos, int tilesize)
{
	const double	half_ptile = game->config.minimap_player_size / 2.0;

	draw_rectangle(game,
		(t_point){pos.x * tilesize + half_ptile, pos.y * tilesize + half_ptile},
		(t_point){(pos.x + 1) * tilesize - half_ptile,
			(pos.y + 1) * tilesize - half_ptile},
		0xFFFF00);
}

static void	draw_minimap(t_var *game, t_dpoint pos, int mapsize, int tilesize)
{
	const int		tot_cells = mapsize / tilesize;
	t_point			start = {ceil(pos.x - tot_cells / 2) - 1, ceil(pos.y - tot_cells / 2) - 1};
	t_point			end = {ceil(pos.x + tot_cells / 2), ceil(pos.y + tot_cells / 2)};
	int				col_start = start.x;
	t_point			c;

	c = (t_point){-1, -1};
	start.y--;
	while (++start.y <= end.y && ++c.y > -1)
	{
		start.x = col_start - 1;
		c.x = -1;
		while (++start.x <= end.x && ++c.x > -1)
		{
			int color = 0x222222;
			if (get_map_at(game, start.y, start.x) == MAP_WALL)
				color = 0xff0000;
			if (get_map_at(game, start.y, start.x) == MAP_FLOOR
				|| chr_is_player(get_map_at(game, start.y, start.x)))
				color = game->config.floor.hex;
			draw_rectangle(game, (t_point){c.x * tilesize, c.y * tilesize},
				(t_point){(c.x + 1) * tilesize, (c.y + 1) * tilesize}, color);
			if (c.x == tot_cells / 2 && c.y == tot_cells / 2)
				draw_player(game, c, tilesize);
		}
	}
}

/*
# Minimap rendering

This function will render the minimap onto the window

## TODOLIST
- [x] Make the minimap of fixed size AxB
- [x] Put the player at center of the minimap (checkout "the witcher"'s minimap)
- [x] Supposedly it's already needed in points above,
	make space for the minimap's zoom/dezoom
*/
void	render_minimap(t_var *game)
{
	int				mapsize;
	const int		tilesize = game->config.minimap_tilesize
		* game->config.minimap_zoom;
	const t_dpoint	pos = {game->player.x_px / game->config.defaults.tilesize,
		game->player.y_px / game->config.defaults.tilesize};

	mapsize = game->config.win_width * game->config.minimap_scale;
	if (game->config.win_height < game->config.win_width)
		mapsize = game->config.win_height * game->config.minimap_scale;
	draw_minimap(game, pos, mapsize, tilesize);
}
