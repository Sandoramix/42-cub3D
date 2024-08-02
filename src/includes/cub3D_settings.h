/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_settings.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:56:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/02 14:53:35 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_SETTINGS_H
# define CUB3D_SETTINGS_H

# include <mlx_int.h>

// SIZING-----------------------------------------------------------------------
# define TILE_SIZE 64
# define MINIMAP_TILE_SIZE 8
//------------------------------------------------------------------------------
//? Serve?
# define PLANEX 0.0
# define PLANEY 0.66

// KEYBINDINGS------------------------------------------------------------------
# define KEY_W XK_w
# define KEY_A XK_a
# define KEY_S XK_s
# define KEY_D XK_d

# define KEY_LEFT XK_Left
# define KEY_RIGHT XK_Right
//------------------------------------------------------------------------------

// FILE-MAP-DEFINITIONS---------------------------------------------------------
# define MAP_WHITELIST "01 NEWS"

# define MAP_UNKNOWN ' '
# define MAP_FLOOR '0'
# define MAP_WALL '1'
# define MAP_PLAYER_NORD 'N'
# define MAP_PLAYER_EAST 'E'
# define MAP_PLAYER_WEST 'W'
# define MAP_PLAYER_SOUTH 'S'

# define FLOOR 0
# define WALL 1

//------------------------------------------------------------------------------
// FILE-SETTINGS-DEFINITION-----------------------------------------------------

/**
 * Define what type of configuration is the given row inside your file
 * @param CNF_UNKNOWN invalid configuration
 * @param CNF_FLOOR floor color
 * @param CNF_CEILING ceiling color
 * @param CNF_WALL_NORD wall's nord sprite
 * @param CNF_WALL_EAST wall's east sprite
 * @param CNF_WALL_WEST wall's west sprite
 * @param CNF_WALL_SOUTH wall's south sprite
 */
typedef enum e_cnf
{
	CNF_UNKNOWN,
	CNF_FLOOR,
	CNF_CEILING,
	CNF_WALL_NORD,
	CNF_WALL_EAST,
	CNF_WALL_WEST,
	CNF_WALL_SOUTH
}	t_cnf;

# define STR_WALL_NORD "NO"
# define STR_WALL_EAST "EA"
# define STR_WALL_WEST "WE"
# define STR_WALL_SOUTH "EA"
# define STR_FLOOR "F"
# define STR_CEILING "C"
//------------------------------------------------------------------------------

/*HARD CODED VALUES (maybe)*/
# define VELOCITY 0.2
# define FOV 66

# define PLAYER_ANGLE 270

#endif
