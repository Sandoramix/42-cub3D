/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:17:25 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:24:59 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	is_config_loaded(t_var *game, t_cnf type)
{
	if (type == CNF_FLOOR)
		return (game->cnf.floor_raw != NULL);
	if (type == CNF_CEILING)
		return (game->cnf.ceiling_raw != NULL);
	if (type == CNF_WALL_NORD)
		return (game->cnf.wall_nord_path != NULL);
	if (type == CNF_WALL_EAST)
		return (game->cnf.wall_east_path != NULL);
	if (type == CNF_WALL_WEST)
		return (game->cnf.wall_east_path != NULL);
	if (type == CNF_WALL_SOUTH)
		return (game->cnf.wall_south_path != NULL);
	return (false);
}

bool	is_config_missing(t_var *game)
{
	return (!is_config_loaded(game, CNF_WALL_NORD)
		|| !is_config_loaded(game, CNF_WALL_EAST)
		|| !is_config_loaded(game, CNF_WALL_WEST)
		|| !is_config_loaded(game, CNF_WALL_SOUTH)
		|| !is_config_loaded(game, CNF_CEILING)
		|| !is_config_loaded(game, CNF_FLOOR));
}
