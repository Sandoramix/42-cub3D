/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:46:42 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/15 10:38:00 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	copy_dpos(t_dpoint *p1, t_dpoint p2)
{
	p1->x = p2.x;
	p1->y = p2.y;
}

void	copy_pos(t_point *p1, t_point p2)
{
	p1->x = p2.x;
	p1->y = p2.y;
}

void	add_dpoint(t_dpoint *p1, t_dpoint p2)
{
	p1->x += p2.x;
	p1->y += p2.y;
}

void	add_point(t_point *p1, t_point p2)
{
	p1->x += p2.x;
	p1->y += p2.y;
}

t_dpoint	calculate_point(t_dpoint start, double angle, double distance)
{
	t_dpoint	end;

	if (angle < 0)
		angle = 360 + angle;
	end.x = start.x + (distance * cos(angle_to_radiant(angle))) * TILE_SIZE;
	end.y = start.y + (distance * sin(angle_to_radiant(angle))) * TILE_SIZE;
	return (end);
}

double	calc_wall_px_hit(t_var *game)
{
	const t_raycast	*engine = &game->engine;
	const t_player	*player = &game->player;
	double			wall_px;

	if (engine->side == CNF_WALL_WEST || engine->side == CNF_WALL_EAST)
		wall_px = player->y_px / TILE_SIZE + engine->wall.dist * engine->dir.y;
	else
		wall_px = player->x_px / TILE_SIZE + engine->wall.dist * engine->dir.x;
	return (wall_px);
}
