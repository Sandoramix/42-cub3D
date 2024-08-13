/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:55:07 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 00:20:01 by odudniak         ###   ########.fr       */
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
				to_rgb(colors[get_map_at(game, dy, dx) != MAP_WALL]));
		}
	}
	render_player(game);
}
