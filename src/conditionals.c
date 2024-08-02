/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:17:25 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/02 18:17:43 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	is_config_missing(t_var *game)
{
	return (!game->config.wall_nord_path
		|| !game->config.wall_east_path
		|| !game->config.wall_west_path
		|| !game->config.wall_south_path
		|| !game->config.ceiling_raw
		|| !game->config.floor_raw);
}
