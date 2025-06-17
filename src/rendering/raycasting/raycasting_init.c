/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:22:51 by rileone           #+#    #+#             */
/*   Updated: 2024/08/18 15:17:11 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "cub3D.h"

void	calc_direction(t_raycast *eng, t_player *pl)
{
	const double	x_axispos = (pl->x
			- eng->map_coords.x) * eng->delta_dist.x;
	const double	x_axisneg = (-pl->x
			+ eng->map_coords.x + 1.0) * eng->delta_dist.x;
	double			y_axispos;
	double			y_axisneg;
	t_dvec2			direction;

	if (eng->dir.x < 0)
		eng->step.x = -1;
	else
		eng->step.x = 1;
	if (eng->dir.y < 0)
		eng->step.y = -1;
	else
		eng->step.y = 1;
	y_axispos = ((pl->y) - eng->map_coords.y)
		* eng->delta_dist.y;
	y_axisneg = ((-pl->y) + eng->map_coords.y + 1.0) * eng->delta_dist.y;
	direction.x = (double [2]){x_axispos, x_axisneg}[eng->dir.x > 0];
	direction.y = (double [2]){y_axispos, y_axisneg}[eng->dir.y > 0];
	dvec2_cpy(&eng->ray, direction);
}

void	init_raycast_vars(t_var *game, t_raycast *eng, t_player *pl, int x)
{
	const double	camera_x = (double)(2.0 * x)
		/ (double)game->cnf.window_width - 1;
	const double	raydirx = pl->dir_x + eng->plane.x
		* camera_x;
	const double	raydiry = pl->dir_y + eng->plane.y
		* camera_x;
	t_dvec2			delta_dist_vect;

	if (eng->dir.x == 0)
		delta_dist_vect.x = 1e30;
	else
		delta_dist_vect.x = fabs(1.0 / eng->dir.x);
	if (eng->dir.y == 0)
		delta_dist_vect.y = 1e30;
	else
		delta_dist_vect.y = fabs(1.0 / eng->dir.y);
	ivec2_cpy(&eng->map_coords, (t_ivec2){pl->x, pl->y});
	dvec2_cpy(&eng->dir, (t_dvec2){raydirx, raydiry});
	dvec2_cpy(&eng->delta_dist, delta_dist_vect);
}
