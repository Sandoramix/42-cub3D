/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_settings.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:56:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 00:53:34 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_SETTINGS_H
# define CUB3D_SETTINGS_H

# include <mlx_int.h>

//------------------------------------------------------------------------------

// KEYBINDINGS------------------------------------------------------------------

# ifdef __linux__
#  include <X11/keysym.h>
#  define KEY_W XK_w
#  define KEY_A XK_a
#  define KEY_S XK_s
#  define KEY_D XK_d
#  define KEY_LEFT XK_Left
#  define KEY_RIGHT XK_Right

#  define ESC_KEY XK_Escape
#  define ESC_KEY XK_Escape

# endif // __linux__

# ifndef KEY_W
#  error "Unsupported platform or no key definitions available."
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

// HERE WE GO AGAIN
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 0
# endif
# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 0
# endif


#endif
