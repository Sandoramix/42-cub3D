/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:51:17 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/27 10:25:45 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	lateinit_config(t_var *game, t_config *cnf)
{
	cnf->minimap_size = cnf->window_height * .35;
	if (cnf->window_width < cnf->window_height)
		cnf->minimap_size = cnf->window_width * .35;
	(void)game;
}

static void	init_modifiers(t_config *cnf)
{
	cnf->speed_mult = 1.0;
	cnf->camera_vert_rot_max = 100;
	cnf->camera_vert_rot_min = -100;
	cnf->jump_force = 1600;
	cnf->jump_limit = 350;
	cnf->rot_lateral_speed = 0.05;
	cnf->rot_vertical_speed = 500;
	cnf->speed = 5;
	cnf->squat_offset = 200;
	cnf->minimap_tilesize = 8;
	cnf->minimap_zoom = 2.;
	cnf->minimap_zoom_inc = 0.5;
	cnf->minimap_zoom_min = 1.0;
	cnf->minimap_zoom_max = 6.0;
}

void	init_config(t_var *game, t_config *cnf)
{
	cnf->window_name = WINDOW_NAME;
	lateinit_config(game, cnf);
	cnf->minimap_tilescount = 32;
	cnf->plane_limit = 0.7;
	cnf->max_raycast_steps = 50;
	init_modifiers(cnf);
}
