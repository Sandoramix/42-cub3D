/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:55:07 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 01:58:30 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	draw_player(t_var *game, t_point pos, int tilesize)
{
	const double	ray_len = .15 * game->config.minimap_zoom;
	const t_rgba	color = hex_to_rgba(0xffff00);
	const double	half_ptile = game->config.minimap_player_size / 2.0;
	t_dpoint		view_line_start;
	t_dpoint		view_line_end;

	draw_rectangle_rgb(game,
		(t_point){pos.x * tilesize + half_ptile, pos.y * tilesize + half_ptile},
		(t_point){(pos.x + 1) * tilesize - half_ptile,
		(pos.y + 1) * tilesize - half_ptile},
		color);
	view_line_start = (t_dpoint){pos.x * tilesize + tilesize / 2,
		pos.y * tilesize + tilesize / 2};
	view_line_end = get_destpoint(view_line_start,
			direction_to_angle(game->player.dir_x, game->player.dir_y),
			ray_len, tilesize);
	draw_line_rgb(game, view_line_start, view_line_end, color);
}

static t_rgba	get_coord_color(t_var *g, t_point pos)
{
	if (get_map_at(g, pos.y, pos.x) == MAP_WALL)
		return (hex_to_rgba(0xff0000));
	if (get_map_at(g, pos.y, pos.x) == MAP_FLOOR
		|| chr_is_player(get_map_at(g, pos.y, pos.x)))
		return (g->config.floor);
	return (hex_to_rgba(0x222222));
}

static void	draw_minimap(t_var *game, t_dpoint pos, int mapsize, int tilesize)
{
	const int		offs = mapsize / tilesize / 2;
	t_point			start;
	t_point			end;
	int				col_start;
	t_point			c;

	start = (t_point){ceil(pos.x - offs) - 1, ceil(pos.y - offs) - 1};
	end = (t_point){ceil(pos.x + offs), ceil(pos.y + offs)};
	col_start = start.x;
	c = (t_point){-1, -1};
	start.y--;
	while (++start.y <= end.y && ++c.y > -1)
	{
		start.x = col_start - 1;
		c.x = -1;
		while (++start.x <= end.x && ++c.x > -1)
		{
			draw_rectangle_rgb(game, (t_point){c.x * tilesize, c.y * tilesize},
				(t_point){(c.x + 1) * tilesize, (c.y + 1) * tilesize},
				get_coord_color(game, start));
		}
	}
}

void	render_minimap(t_var *game)
{
	int				mapsize;
	const int		tilesize = game->config.defaults.minimap_tilesize
		* game->config.minimap_zoom;
	const t_dpoint	pos = {game->player.x_px / game->config.defaults.tilesize,
		game->player.y_px / game->config.defaults.tilesize};

	mapsize = game->config.win_width * game->config.minimap_scale;
	if (game->config.win_height < game->config.win_width)
		mapsize = game->config.win_height * game->config.minimap_scale;
	draw_minimap(game, pos, mapsize, tilesize);
	draw_player(game, (t_point){mapsize / tilesize / 2, mapsize / tilesize / 2},
		tilesize);
}
