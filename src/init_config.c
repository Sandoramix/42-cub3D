/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:51:17 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 01:15:15 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/**
 * @brief Get "default" configurations from MACROS
 * TODO (may as well migrate them here)
 * @param def default values' struct
 */
static void	fill_defaults(t_cnfdefaults *def)
{
	def->tilesize = 64;
	def->minimap_tilesize = 4;
	def->camera_z_rot_max = 100;
	def->camera_z_rot_min = -100;
	def->fog_distance = 20;
	def->fov = 66;
	def->jump_force = 1600;
	def->jump_limit = 350;
	def->max_raysteps = 100;
	def->rot_speed = .05;
	def->safety_wall_dist = 1;
	def->speed = 500;
	def->squat_offset = 200;
	def->window_name = WINDOW_NAME;
}

void	init_config(t_var *game, t_config *config)
{
	config->plane_limit = 0.7;
	config->minimap_scale = .25;
	config->minimap_zoom = 2.;
	config->minimap_zoom_min = 1.5;
	config->minimap_zoom_max = 5.0;
	config->minimap_player_size = 4.;
	fill_defaults(&config->defaults);
	game->player.speed_mult = 1.0;
}
