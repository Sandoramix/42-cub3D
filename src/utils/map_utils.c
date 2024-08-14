/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:31:51 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 02:32:17 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

char	get_map_at(t_var *game, int row_idx, int col_idx)
{
	if (row_idx < 0 || row_idx >= game->mapinfo.rows_mtx)
		return (0);
	if (col_idx < 0 || col_idx >= str_ilen(game->mapinfo.map[row_idx]))
		return (0);
	return (game->mapinfo.map[row_idx][col_idx]);
}

bool	can_player_go_here(t_var *game, double x, double y)
{

	if (x < 1
		|| x >= game->mapinfo.cols_mtx - 1
		|| y < 1
		|| y >= game->mapinfo.rows_mtx - 1
		|| get_map_at(game, (y), (x)) == MAP_WALL)
	{
		if (ft_isdebug())
			printf("Can't move,"
				"the player position will be [%.2f][%.2f]\n", x, y);
		return (false);
	}
	return (true);
}
