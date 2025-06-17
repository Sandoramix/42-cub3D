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

void	copy_dpos(t_dvec2 *p1, t_dvec2 p2)
{
	p1->x = p2.x;
	p1->y = p2.y;
}

void	copy_pos(t_ivec2 *p1, t_ivec2 p2)
{
	p1->x = p2.x;
	p1->y = p2.y;
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
	const double	units = game->cnf.tilesize;
	const t_raycast	*engine = &game->engine;
	const t_player	*player = &game->player;
	double			wall_px;

	if (engine->side == CNF_WALL_WEST || engine->side == CNF_WALL_EAST)
		wall_px = player->y_px / units + engine->wall.dist * engine->dir.y;
	else
		wall_px = player->x_px / units + engine->wall.dist * engine->dir.x;
	return (wall_px);
}
