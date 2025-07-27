/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:55:07 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/27 11:31:28 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static t_argb	get_coord_color(t_var *g, t_ivec2 pos)
{
	char	tile;

	tile = get_map_at(g, pos.y, pos.x);
	if (tile == TILE_WALL)
		return (hex_to_argb(0xff0000));
	if (tile == TILE_FLOOR
		|| chr_is_player(tile))
		return (g->cnf.floor);
	return (hex_to_argb(0x222222));
}

static void	draw_pixel_minimap(t_var *g, int x, int y, t_dvec2 top_left)
{
	t_dvec2	map_pos;
	t_ivec2	map_tile;
	double	ppu;

	ppu = g->cnf.minimap_tilesize * g->cnf.minimap_zoom;
	map_pos.x = top_left.x + (x) / ppu;
	map_pos.y = top_left.y + (y) / ppu;
	map_tile.x = (int)floor(map_pos.x);
	map_tile.y = (int)floor(map_pos.y);
	draw_pixel_rgb(g, (t_ivec2){.x = x, .y = y},
		get_coord_color(g, map_tile));
}

static void	draw_minimap(t_var *g, t_dvec2 top_left)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->cnf.minimap_size)
	{
		x = 0;
		while (x < g->cnf.minimap_size)
		{
			draw_pixel_minimap(g, x, y, top_left);
			x++;
		}
		y++;
	}
}

void	draw_player(t_var *g)
{
	t_dvec2	center;
	t_dvec2	ray_end;
	double	half;

	half = g->cnf.minimap_tilesize * g->cnf.minimap_zoom / 2.0;
	center.x = g->cnf.minimap_size / 2.0;
	center.y = g->cnf.minimap_size / 2.0;
	half *= .75;
	draw_circle_rgb(g, (t_ivec2){.x = center.x, .y = center.y},
		half, hex_to_argb(0xffff00));
	ray_end = get_destpoint(center,
			direction_to_angle(g->player.dir.x, g->player.dir.y),
			0.5, g->cnf.minimap_tilesize * g->cnf.minimap_zoom);
	draw_line_rgb(g, center, ray_end, hex_to_argb(0x00ff00));
}

void	render_minimap(t_var *g)
{
	t_dvec2	top_left;

	top_left.x = g->player.pos.x
		- (g->cnf.minimap_size / 2.0)
		/ (g->cnf.minimap_tilesize * g->cnf.minimap_zoom);
	top_left.y = g->player.pos.y
		- (g->cnf.minimap_size / 2.0)
		/ (g->cnf.minimap_tilesize * g->cnf.minimap_zoom);
	draw_minimap(g, top_left);
	draw_player(g);
}
