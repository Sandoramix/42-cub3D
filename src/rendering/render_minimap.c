/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:55:07 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/15 15:52:49 by odudniak         ###   ########.fr       */
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

static void	draw_borders(t_var *game, int size)
{
	draw_rectangle(game, (t_point){0, 0}, (t_point){1, size}, 0x0);
	draw_rectangle(game, (t_point){size - 1, 0}, (t_point){size, size}, 0x0);
	draw_rectangle(game, (t_point){0, 0}, (t_point){size, 1}, 0x0);
	draw_rectangle(game, (t_point){0, size - 1}, (t_point){size, size}, 0x0);
}

static void	draw_player(t_var *game, t_config *cnf, int mapsize)
{
	const int		tilesize = cnf->minimap_player_size;
	const int		center = mapsize / 2;

	draw_rectangle(game,
		(t_point){center - tilesize / 2, center - tilesize / 2},
		(t_point){center + tilesize / 2, center + tilesize / 2},
		0xFFFF00);
}

static void	draw_minimap(t_var *game, t_dpoint pos, int mapsize, int tilesize)
{
	const int		tot_cells = mapsize / tilesize;
	t_dpoint			start = {pos.x - tot_cells / 2, pos.y - tot_cells / 2 - 1};
	t_dpoint			end = {pos.x + tot_cells / 2, pos.y + tot_cells / 2};
	int				col_start = start.x;
	int				y;
	int				x;

	y = 0;
	while (++start.y <= end.y)
	{
		start.x = col_start - 1;
		x = 0;
		while (++start.x <= end.x)
		{
			int color = 0x222222;
			if (get_map_at(game, start.y, start.x) == MAP_WALL)
				color = 0xff0000;
			if (get_map_at(game, start.y, start.x) == MAP_FLOOR
				|| chr_is_player(get_map_at(game, start.y, start.x)))
				color = game->config.floor.hex;
			draw_rectangle(game, (t_point){x * tilesize, y * tilesize},
				(t_point){(x + 1) * tilesize, (y + 1) * tilesize}, color);
			x++;
		}
		y++;
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
	draw_player(game, &game->config, mapsize);
	draw_borders(game, mapsize);
}
