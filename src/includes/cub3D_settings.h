/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_settings.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:56:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/18 15:18:25 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_SETTINGS_H
# define CUB3D_SETTINGS_H

# include <mlx_int.h>

// KEYBINDINGS------------------------------------------------------------------

# ifdef __linux__
#  include <X11/keysym.h>
#  define MOVE_FORWARD XK_w
#  define MOVE_LEFT XK_a
#  define MOVE_BACKWARD XK_s
#  define MOVE_RIGHT XK_d

#  define LOOK_UP XK_Up
#  define LOOK_DOWN XK_Down
#  define LOOK_LEFT XK_Left
#  define LOOK_RIGHT XK_Right

#  define ESC_KEY XK_Escape

#  define JUMP XK_space
#  define SQUAT XK_Control_L

#  define GUARD XK_Alt_L

#  define SPRINT XK_Shift_L

#  define MINIMAP_ZOOM_IN XK_Page_Up
#  define MINIMAP_ZOOM_OUT XK_Page_Down

# endif // __linux__

# ifndef MOVE_FORWARD
#  error "Unsupported platform or no key definitions available. \
Please try it on Linux with X11Lib"
# endif
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
	CNF_WALL_SOUTH,
}	t_cnf;

# define STR_WALL_NORD "NO"
# define STR_WALL_EAST "EA"
# define STR_WALL_WEST "WE"
# define STR_WALL_SOUTH "SO"
# define STR_FLOOR "F"
# define STR_CEILING "C"
//------------------------------------------------------------------------------

//TEXTURES----------------------------------------------------------------------
# define TEXTURE_RESTING_R "assets/sprites/restingR.xpm"
# define TEXTURE_BLOCK_R "assets/sprites/blockR.xpm"
# define TEXTURE_ATTACK0_R "assets/sprites/attack0R.xpm"
# define TEXTURE_ATTACK1_R "assets/sprites/attack1R.xpm"
# define TEXTURE_ATTACK2_R "assets/sprites/attack2R.xpm"

# ifndef WINDOW_NAME
#  define WINDOW_NAME "cub3D"
# endif

// WINDOW SIZING. IF set to 0, the screen's size will be taken
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 0
# endif
# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 0
# endif

#endif
