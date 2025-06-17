/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:46:42 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:25:30 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	dvec2_cpy(t_dvec2 *dest, t_dvec2 src)
{
	dest->x = src.x;
	dest->y = src.y;
}

void	ivec2_cpy(t_ivec2 *dest, t_ivec2 src)
{
	dest->x = src.x;
	dest->y = src.y;
}

t_dvec2	get_destpoint(t_dvec2 start, double angle,
	double distance, double units)
{
	t_dvec2	end;

	if (angle < 0)
		angle = 360 + angle;
	end.x = start.x + (distance * cos(angle_to_radiant(angle))) * units;
	end.y = start.y + (distance * sin(angle_to_radiant(angle))) * units;
	return (end);
}

double	calc_wall_px_hit(t_var *game)
{
	const t_raycast	*engine = &game->engine;
	const t_player	*player = &game->player;
	double			wall_px;

	if (engine->side == CNF_WALL_WEST || engine->side == CNF_WALL_EAST)
		wall_px = player->y_px + engine->wall.dist * engine->dir.y;
	else
		wall_px = player->x_px + engine->wall.dist * engine->dir.x;
	return (wall_px);
}
