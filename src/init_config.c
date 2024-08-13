/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:51:17 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 00:52:36 by odudniak         ###   ########.fr       */
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
	config->minimap_scale = 8;
	config->minimap_player_scale = 4;
	fill_defaults(&config->defaults);
}
