/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:55:07 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/12 18:07:27 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	render_player(t_var *game)
{
	t_dpoint				playerpos;
	const int				tile_scale = game->config.minimap_scale;
	const int				player_scale = game->config.minimap_player_scale;

	playerpos = (t_dpoint)
	{game->player.x_px / TILE_SIZE * tile_scale,
	game->player.y_px / TILE_SIZE * tile_scale};

	// TODO keep the player in bounds.
	draw_rectangle(game, (t_point){playerpos.x, playerpos.y},
		(t_point){playerpos.x + player_scale, playerpos.y + player_scale},
		0xFF0000);
}

void	render_minimap(t_var *game)
{
	const int				scale = game->config.minimap_scale;
	const unsigned long		colors[2] = {0xD7D7D7ff, 0x000000ff};
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
				to_rgb(colors[get_map_at(game, dy, dx) != MAP_WALL]));
		}
	}
	render_player(game);
}
