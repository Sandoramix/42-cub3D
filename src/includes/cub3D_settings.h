/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_settings.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:56:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/07/31 17:13:59 by odudniak         ###   ########.fr       */
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
//------------------------------------------------------------------------------

# define MAP_WHITELIST "01 NEWS"

# define MAP_UNKNOWN ' '
# define MAP_FLOOR '0'
# define MAP_WALL '1'
# define MAP_PLAYER_NORD 'N'
# define MAP_PLAYER_EAST 'E'
# define MAP_PLAYER_WEST 'W'
# define MAP_PLAYER_SUD 'S'

# define FLOOR 0
# define WALL 1

# define VELOCITY 1000
# define FOV 60

#endif
