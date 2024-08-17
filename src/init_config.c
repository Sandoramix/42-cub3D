/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:51:17 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:58:43 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	init_modifiers(t_config *cnf)
{
	cnf->speed_mult = 1.0;
	cnf->camera_vert_rot_max = 100;
	cnf->camera_vert_rot_min = -100;
	cnf->jump_force = 1600;
	cnf->jump_limit = 350;
	cnf->rot_speed = .05;
	cnf->speed = 500;
	cnf->squat_offset = 200;
	cnf->minimap_window_scale = .25;
	cnf->minimap_zoom = 2.;
	cnf->minimap_zoom_min = 1.5;
	cnf->minimap_zoom_max = 5.0;
}

void	init_config(t_config *cnf)
{
	cnf->window_name = WINDOW_NAME;
	cnf->tilesize = 64;
	cnf->minimap_tilesize = 4;
	cnf->minimap_tilesize_player = 4.;
	cnf->plane_limit = 0.7;
	init_modifiers(cnf);
}
