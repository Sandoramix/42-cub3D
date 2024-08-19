/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:14:49 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/19 15:14:58 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	can_player_go_here(t_var *game, double x, double y)
{
	if (x < 0
		|| x >= game->map.cols_mtx - 1
		|| y < 0
		|| y >= game->map.rows_mtx - 1
		|| get_map_at(game, (y), (x)) == MAP_WALL)
	{
		return (false);
	}
	return (true);
}
