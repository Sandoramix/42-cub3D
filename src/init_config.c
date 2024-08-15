/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:51:17 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/15 15:45:29 by odudniak         ###   ########.fr       */
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
	def->tilesize = TILE_SIZE;
	def->camera_z_rot_max = CAMERA_HIGH_LIMIT;
	def->camera_z_rot_min = CAMERA_LOW_LIMIT;
	def->fog_distance = FOG_DISTANCE;
	def->fov = FOV;
	def->jump_force = Z_ACCELLERATION;
	def->jump_limit = JUMP_LIMIT;
	def->max_raysteps = MAX_RAYSTEPS;
	def->rot_speed = ROTATION_SPEED;
	def->safety_wall_dist = SAFETY_WALL_DIST;
	def->speed = VELOCITY;
	def->squat_offset = CROUCH_HEIGHT;
	def->window_name = WINDOW_NAME;
}

void	init_config(t_config *config)
{
	config->plane_limit = 0.7;
	config->minimap_scale = .25;
	config->minimap_tilesize = 4;
	config->minimap_zoom = 2.5;
	config->minimap_zoom_min = 1.0;
	config->minimap_zoom_max = 4.0;
	config->minimap_player_size = 4.;
	fill_defaults(&config->defaults);
}
