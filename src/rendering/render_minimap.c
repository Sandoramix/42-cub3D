/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:55:07 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 00:00:24 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	point_inside_window(t_var *game, t_dpoint point)
{
	return (point.x >= 0 && point.y >= 0
		&& point.x < game->config.win_width
		&& point.y < game->config.win_height);
}

void draw_line(t_var *game, t_dpoint start, t_dpoint end, t_rgba rgb)
{
	t_dpoint	delta;
	t_dpoint	increment;
	t_dpoint	next_point;
	int			pixels;
	int			counter;

	delta = (t_dpoint){end.x - start.x, end.y - start.y};
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	increment = (t_dpoint){delta.x / pixels, delta.y / pixels};
	next_point = (t_dpoint){start.x, start.y};
	counter = -1;
	while (++counter < pixels && point_inside_window(game, next_point))
	{
		draw_pixel_rgb(game, next_point.x, next_point.y, rgb);
		next_point.x += increment.x;
		next_point.y += increment.y;
	}
}

double	direction_to_angle(double x, double y)
{
	const double	angle_rad = atan2(y, x);
	double			angle_deg;

	angle_deg = angle_rad * (180.0 / pi());
	if (angle_deg < 0)
		angle_deg += 360.0;
	return (angle_deg);
}

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
	draw_line(game, view_line_start, view_line_end, color);
}

//TODO norminette me
static void	draw_minimap(t_var *game, t_dpoint pos, int mapsize, int tilesize)
{
	const int		offs = mapsize / tilesize / 2;
	t_point			start = {ceil(pos.x - offs) - 1, ceil(pos.y - offs) - 1};
	t_point			end = {ceil(pos.x + offs), ceil(pos.y + offs)};
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
		}
	}
}

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
	draw_player(game, (t_point){mapsize / tilesize / 2, mapsize / tilesize / 2},
		tilesize);
}
