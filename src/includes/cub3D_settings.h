/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_settings.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:56:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/03 08:17:00 by odudniak         ###   ########.fr       */
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

# ifdef __APPLE__
#  include <TargetConditionals.h>
#  if TARGET_OS_MAC

#   ifdef __CARBON__
// Carbon headers
#    include <Carbon/Carbon.h>
#    define KEY_W kVK_ANSI_W
#    define KEY_A kVK_ANSI_A
#    define KEY_S kVK_ANSI_S
#    define KEY_D kVK_ANSI_D
#    define KEY_LEFT kVK_LeftArrow
#    define KEY_RIGHT kVK_RightArrow
#    define ESC_KEY kVK_Escape

// Cocoa headers
#   elif defined(__COCOA__)
#    include <Cocoa/Cocoa.h>
#    define KEY_W 'w'
#    define KEY_A 'a'
#    define KEY_S 's'
#    define KEY_D 'd'
#    define KEY_LEFT NSLeftArrowFunctionKey
#    define KEY_RIGHT NSRightArrowFunctionKey
#	 define ESC_KEY kVK_Escape

// IOKit headers
#   elif defined(__IOKIT__)
#    include <IOKit/hidsystem/IOLLEvent.h>
#    define KEY_W kHIDUsage_KeyboardW
#    define KEY_A kHIDUsage_KeyboardA
#    define KEY_S kHIDUsage_KeyboardS
#    define KEY_D kHIDUsage_KeyboardD
#    define KEY_LEFT kHIDUsage_KeyboardLeftArrow
#    define KEY_RIGHT kHIDUsage_KeyboardRightArrow
#    define ESC_KEY kHIDUsage_KeyboardEscape

#   else
#    error "No supported keyboard handling library found for macOS."
#   endif

#  endif // TARGET_OS_MAC
# endif // __APPLE__

# ifdef __linux__
#  include <X11/keysym.h>
#  define KEY_W XK_w
#  define KEY_A XK_a
#  define KEY_S XK_s
#  define KEY_D XK_d
#  define KEY_LEFT XK_Left
#  define KEY_RIGHT XK_Right
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

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_NAME "UrMom!"	

#endif
