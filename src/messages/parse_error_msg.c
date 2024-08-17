/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:11:06 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:24:59 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	print_missing_config(t_var *game)
{
	if (is_config_missing(game))
		ft_perror("Error: missing configurations:\n");
	if (!game->cnf.floor_raw)
		ft_perror("- "STR_FLOOR" <color>\n");
	if (!game->cnf.ceiling_raw)
		ft_perror("- "STR_CEILING" <color>\n");
	if (!game->cnf.wall_nord_path)
		ft_perror("- "STR_WALL_NORD" <path>\n");
	if (!game->cnf.wall_east_path)
		ft_perror("- "STR_WALL_EAST" <path>\n");
	if (!game->cnf.wall_west_path)
		ft_perror("- "STR_WALL_WEST" <path>\n");
	if (!game->cnf.wall_south_path)
		ft_perror("- "STR_WALL_SOUTH" <path>\n");
}
