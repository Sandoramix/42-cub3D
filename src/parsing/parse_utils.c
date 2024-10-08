/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:07:56 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:24:59 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_parse.h>

void	*parse_get_config_pointed_data(t_var *game, t_cnf type)
{
	if (type == CNF_FLOOR)
		return (&game->cnf.floor);
	if (type == CNF_CEILING)
		return (&game->cnf.ceiling);
	if (type == CNF_WALL_NORD)
		return (&game->cnf.wall_nord);
	if (type == CNF_WALL_EAST)
		return (&game->cnf.wall_east);
	if (type == CNF_WALL_WEST)
		return (&game->cnf.wall_west);
	if (type == CNF_WALL_SOUTH)
		return (&game->cnf.wall_south);
	return (NULL);
}

char	**parse_get_config_pointed_str(t_var *game, t_cnf type)
{
	if (type == CNF_FLOOR)
		return (&game->cnf.floor_raw);
	if (type == CNF_CEILING)
		return (&game->cnf.ceiling_raw);
	if (type == CNF_WALL_NORD)
		return (&game->cnf.wall_nord_path);
	if (type == CNF_WALL_EAST)
		return (&game->cnf.wall_east_path);
	if (type == CNF_WALL_WEST)
		return (&game->cnf.wall_west_path);
	if (type == CNF_WALL_SOUTH)
		return (&game->cnf.wall_south_path);
	return (NULL);
}

t_cnf	parse_identify_cnf(char *line)
{
	if (str_startswith(line, STR_FLOOR" "))
		return (CNF_FLOOR);
	if (str_startswith(line, STR_CEILING" "))
		return (CNF_CEILING);
	if (str_startswith(line, STR_WALL_NORD" "))
		return (CNF_WALL_NORD);
	if (str_startswith(line, STR_WALL_EAST" "))
		return (CNF_WALL_EAST);
	if (str_startswith(line, STR_WALL_WEST" "))
		return (CNF_WALL_WEST);
	if (str_startswith(line, STR_WALL_SOUTH" "))
		return (CNF_WALL_SOUTH);
	return (CNF_UNKNOWN);
}

bool	parse_config_val_is_path(t_cnf type)
{
	return (type != CNF_CEILING && type != CNF_FLOOR);
}
