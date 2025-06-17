/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:31:51 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:24:59 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

char	get_map_at(t_var *game, int row_idx, int col_idx)
{
	if (row_idx < 0 || row_idx >= game->map.rows_mtx)
		return (0);
	if (col_idx < 0 || col_idx >= str_ilen(game->map.map[row_idx]))
		return (0);
	return (game->map.map[row_idx][col_idx]);
}

bool	can_player_go_here(t_var *game, double x, double y)
{
	if (x < 0
		|| x >= game->map.cols_mtx - 1
		|| y < 0
		|| y >= game->map.rows_mtx - 1
		|| get_map_at(game, (y), (x)) == TILE_WALL)
	{
		return (false);
	}
	return (true);
}

bool	is_point_inside_window(t_var *game, t_dvec2 point)
{
	return (point.x >= 0 && point.y >= 0
		&& point.x < game->cnf.window_width
		&& point.y < game->cnf.window_height);
}
